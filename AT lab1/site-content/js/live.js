var Point = function(){};
Point.prototype = {
	x: null,
	y: null
};

var Cell = function(){};
Cell.prototype = {
	age: 0,

	grow: function()
	{
		this.age++;
	},

	getColor: function()
	{
		color = this.age * 5;
		if (color > 250)
			color = 250;

		return 'hsl(' + color + ', 100%, 50%)';
	}
}

var World = function()
{
	var x = 10,
		y = 10;
		
	var configuration = 0;

	if (arguments.length === 1)
		x = y = parseInt(arguments[0]);
	else if (arguments.length === 2) {
		x = parseInt(arguments[0]);
		y = parseInt(arguments[1]);
	}
	else if (arguments.length === 3) {
		x = parseInt(arguments[0]);
		y = parseInt(arguments[1]);
		configuration = parseInt(arguments[2]);
	}

	this.init(x, y, configuration);
};

World.prototype = {
	size: new Point,
	speed: 100,

	drawCellCallback: function(x, y, color){},
	eraseCellCallback: function(x, y){},

	age: 0,
	map: [],

	started: false,

	_borderMap: [],
	_changeQueue: [],
	_timeout: null,

	init: function(x, y, configuration)
	{
		this.age = 0;

		this.size.x = x;
		this.size.y = y;

		this.map = [];
		for (var i = 0; i <= this.size.x; i++)
			this.map[i] = [];

		switch (configuration)
		{
			case 1:
				this.startGlaider();
				break;
		    case 2:
			    this.startGosper();
				break;
			case 3:
			    this.startStick();
				break;
			case 4:
				this.startBreaker();
				break;
			case 5:
				this.startCat();
				break;
			default:
				this.startDefault();			
		}		

		this._changeQueue = [
			[undefined, undefined],
			[undefined, undefined]
		];

	},
	
	startDefault: function()
	{
		var x = 0;
		var y = 0;
		
		for (var i = 0; i < (this.size.x * this.size.y) / 2; i++) {
			x = Math.round(Math.random() * size.x);
			if (!this.map[x])
				this.map[x] = [];

			y = Math.round(Math.random() * size.y);
			this.map[x][y] = new Cell;

			this.drawCellCallback(x, y);
		}
	},
	
	startGosper: function()
	{
		var points = [[10, 14], [11, 13], [11, 14], [20, 12], [20, 13], [20, 14], [21, 11], [21, 15], [22, 10], [22, 16], [23, 10], [23, 16],
					  [33, 13], [33, 17], [34, 12], [34, 13], [34, 17], [34, 18], [36, 14], [36, 15], [36, 16], [37, 14], [37, 15], [37, 16],
					  [38, 15], [44, 16], [45, 15], [45, 16]];
	    for (var index = 0; index < points.length; ++index)
		{
			this.createCell(points[index][0], points[index][1]);
		}
	},
	
	startGlaider: function()
	{
		var points = [[10, 12], [11, 10], [12, 10], [13, 10], [13, 11]];
		for (var index = 0; index < points.length; ++index)
		{
			this.createCell(points[index][0], points[index][1]);
		}
	},
	
	startCat: function()
	{		
		var points = [[10, 12], [10, 13], [10, 14], [11, 10], [11, 11], [11, 15], [12, 11], [12, 13], [12, 15], [13, 11], [13, 13], [13, 15],
					  [14, 10], [14, 11], [14, 15], [15, 12], [15, 13], [15, 14]];
		for (var index = 0; index < points.length; ++index)
		{
			this.createCell(points[index][0], points[index][1]);
		}
	},
	
	startStick: function()
	{
		var points = [[10, 10], [10, 11], [11, 10], [12, 11], [12, 13], [14, 13], [14, 15], [16, 15], [16, 17], [18, 17], [18, 19], [20, 19],
					  [20, 21], [21, 22], [22, 21], [22, 22]];
		for (var index = 0; index < points.length; ++index)
		{
			this.createCell(points[index][0], points[index][1]);
		}
	},
	
	startBreaker: function()
	{
		var points = [[10, 13], [10, 14], [10, 15], [11, 10], [11, 11], [11, 15], [12, 10], [12, 11], [12, 12], [12, 13], [12, 14], [14, 10],
					  [14, 11], [14, 12], [14, 13], [14, 14], [15, 10], [15, 11], [15, 15], [16, 13], [16, 14], [16, 15]];
		for (var index = 0; index < points.length; ++index)
		{
			this.createCell(points[index][0], points[index][1]);
		}
	},

	start: function()
	{
		this.started = true;
		this.step();
	},

	stop: function()
	{
		clearTimeout(this._timeout);
		this.started = false;
	},

	step: function()
	{
		this.age++;

		this._borderMap = [];

		var burnNote = [],
			deathNote = [];

		var cnt = 0;
		var color;

		for (var i in this.map) {
			for (var j in this.map[i]) {

				cnt = this.checkNeighbors(i, j, true);

				if (cnt < 2 || cnt > 3)
					deathNote.push([i, j]);

				this.drawCellCallback(i, j, this.map[i][j].getColor());

				this.map[i][j].grow();
			}
		}

		for (var i in this._borderMap) {
			for (var j in this._borderMap[i]) {

				cnt = this.checkNeighbors(i, j, false);

				if (cnt === 3)
					burnNote.push([i, j]);
			}
		}

		for (var i in burnNote)
			this.burnCell(burnNote[i][0], burnNote[i][1]);


		for (var i in deathNote)
			this.killCell(
				deathNote[i][0],
				deathNote[i][1]
			);

		if (!deathNote.length)
			this.stop();

		this._changeQueue.push([burnNote.length, deathNote.length]);
		if (this._changeQueue.length > 3)
			this._changeQueue.shift();

		if (this.started) {
			var that = this;
			this._timeout = setTimeout(
				function()
				{
					if (that.started)
						that.step();
				},
				this.speed
			);
		}
		
	},

	checkNeighbors: function(x, y, toCheckList)
	{

		var count = 0,
			ox = 0,
			oy = 0;

		x = parseInt(x);
		y = parseInt(y);

		var width = this.size.x + 1,
			height = this.size.y + 1;

		for (var i = x - 1; i <= x + 1; i++) {
			ox = (i + width) % width;

			for (var j = y - 1; j <= y + 1; j++) {
				if (i === x && j === y)
					continue;

				oy = (j + height) % height;

				if (this.map[ox] && this.map[ox][oy] !== undefined)
					count++;
				else if (toCheckList) {
					if (!this._borderMap[ox])
						this._borderMap[ox] = [];
					this._borderMap[ox][oy] = true;
				}
			}
		}

		return count;
	},

	burnCell: function(x, y)
	{
		if (!this.map[x])
			this.map[x] = [];
		this.map[x][y] = new Cell;

		this.drawCellCallback(x, y, 'hsl(350, 100%, 50%)');
	},

	killCell: function(x, y)
	{
		delete this.map[x][y];

		this.eraseCellCallback(x, y);
	},

	clear: function()
	{
		for (var i in this.map)
			for (var j in this.map[i])
				this.killCell(i, j);
	},
	
	createCell: function(x, y)
	{
		this.map[x][y] = new Cell;
		this.drawCellCallback(x, y);
	}
}
