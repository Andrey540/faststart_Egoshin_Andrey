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
		this.map[10][14] = new Cell;
		this.map[11][13] = new Cell;
		this.map[11][14] = new Cell;
		
		this.map[20][12] = new Cell;
		this.map[20][13] = new Cell;
		this.map[20][14] = new Cell;
		this.map[21][11] = new Cell;
		this.map[21][15] = new Cell;
		this.map[22][10] = new Cell;
		this.map[22][16] = new Cell;
		this.map[23][10] = new Cell;
		this.map[23][16] = new Cell;
		
		this.map[33][13] = new Cell;
		this.map[33][17] = new Cell;
		this.map[34][12] = new Cell;
		this.map[34][13] = new Cell;
		this.map[34][17] = new Cell;
		this.map[34][18] = new Cell;
		this.map[36][14] = new Cell;
		this.map[36][15] = new Cell;
		this.map[36][16] = new Cell;
		this.map[37][14] = new Cell;
		this.map[37][15] = new Cell;
		this.map[37][16] = new Cell;
		this.map[38][15] = new Cell;
		
		this.map[44][16] = new Cell;
		this.map[45][15] = new Cell;
		this.map[45][16] = new Cell;

		this.drawCellCallback(10, 14);
		this.drawCellCallback(11, 13);
		this.drawCellCallback(11, 14);
		
		this.drawCellCallback(20, 12);
		this.drawCellCallback(20, 13);
		this.drawCellCallback(20, 14);
		this.drawCellCallback(21, 11);
		this.drawCellCallback(21, 15);
		this.drawCellCallback(22, 10);
		this.drawCellCallback(22, 16);
		this.drawCellCallback(23, 10);
		this.drawCellCallback(23, 16);
		
		this.drawCellCallback(33, 13);
		this.drawCellCallback(33, 17);
		this.drawCellCallback(34, 12);
		this.drawCellCallback(34, 13);
		this.drawCellCallback(34, 17);
		this.drawCellCallback(34, 18);
		this.drawCellCallback(36, 14);
		this.drawCellCallback(36, 15);
		this.drawCellCallback(36, 16);
		this.drawCellCallback(37, 14);
		this.drawCellCallback(37, 15);
		this.drawCellCallback(37, 16);
		this.drawCellCallback(38, 15);
		
		this.drawCellCallback(44, 16);
		this.drawCellCallback(45, 13);
		this.drawCellCallback(45, 16);
	},
	
	startGlaider: function()
	{
		this.map[10][12] = new Cell;
		this.map[11][10] = new Cell;
		this.map[12][10] = new Cell;
		this.map[13][10] = new Cell;
		this.map[13][11] = new Cell;

		this.drawCellCallback(10, 12);
		this.drawCellCallback(11, 10);
		this.drawCellCallback(12, 10);
		this.drawCellCallback(13, 10);
		this.drawCellCallback(13, 11);
	},
	
	startCat: function()
	{
		this.map[10][12] = new Cell;
		this.map[10][13] = new Cell;
		this.map[10][14] = new Cell;
		this.map[11][10] = new Cell;
		this.map[11][11] = new Cell;
		this.map[11][15] = new Cell;
		this.map[12][11] = new Cell;
		this.map[12][13] = new Cell;
		this.map[12][15] = new Cell;
		this.map[13][11] = new Cell;
		this.map[13][13] = new Cell;
		this.map[13][15] = new Cell;
		this.map[14][10] = new Cell;
		this.map[14][11] = new Cell;
		this.map[14][15] = new Cell;
		this.map[15][12] = new Cell;
		this.map[15][13] = new Cell;
		this.map[15][14] = new Cell;

		this.drawCellCallback(10, 12);
		this.drawCellCallback(10, 13);
		this.drawCellCallback(10, 14);
		this.drawCellCallback(11, 10);
		this.drawCellCallback(11, 11);
		this.drawCellCallback(11, 15);
		this.drawCellCallback(12, 11);
		this.drawCellCallback(12, 13);
		this.drawCellCallback(12, 15);
		this.drawCellCallback(13, 11);
		this.drawCellCallback(13, 13);
		this.drawCellCallback(13, 15);
		this.drawCellCallback(14, 10);
		this.drawCellCallback(14, 11);
		this.drawCellCallback(14, 15);
		this.drawCellCallback(15, 12);
		this.drawCellCallback(15, 13);
		this.drawCellCallback(15, 14);
	},
	
	startStick: function()
	{
		this.map[10][10] = new Cell;
		this.map[10][11] = new Cell;
		this.map[11][10] = new Cell;
		this.map[12][11] = new Cell;
		this.map[12][13] = new Cell;
		this.map[14][13] = new Cell;
		this.map[14][15] = new Cell;
		this.map[16][15] = new Cell;
		this.map[16][17] = new Cell;
		this.map[18][17] = new Cell;
		this.map[18][19] = new Cell;
		this.map[20][19] = new Cell;
		this.map[20][21] = new Cell;
		this.map[21][22] = new Cell;
		this.map[22][21] = new Cell;
		this.map[22][22] = new Cell;

		this.drawCellCallback(10, 10);
		this.drawCellCallback(10, 11);
		this.drawCellCallback(11, 10);
		this.drawCellCallback(12, 11);
		this.drawCellCallback(12, 13);
		this.drawCellCallback(14, 13);
		this.drawCellCallback(14, 15);
		this.drawCellCallback(16, 15);
		this.drawCellCallback(16, 17);
		this.drawCellCallback(18, 17);
		this.drawCellCallback(18, 19);
		this.drawCellCallback(20, 19);
		this.drawCellCallback(20, 21);
		this.drawCellCallback(21, 22);
		this.drawCellCallback(22, 21);
		this.drawCellCallback(22, 22);
	},
	
	startBreaker: function()
	{
		this.map[10][13] = new Cell;
		this.map[10][14] = new Cell;
		this.map[10][15] = new Cell;		
		this.map[11][10] = new Cell;		
		this.map[11][11] = new Cell;
		this.map[11][15] = new Cell;
		this.map[12][10] = new Cell;
		this.map[12][11] = new Cell;
		this.map[12][12] = new Cell;
		this.map[12][13] = new Cell;
		this.map[12][14] = new Cell;
		
		this.map[14][10] = new Cell;
		this.map[14][11] = new Cell;
		this.map[14][12] = new Cell;
		this.map[14][13] = new Cell;
		this.map[14][14] = new Cell;
		this.map[15][10] = new Cell;		
		this.map[15][11] = new Cell;
		this.map[15][15] = new Cell;
		this.map[16][13] = new Cell;
		this.map[16][14] = new Cell;
		this.map[16][15] = new Cell;
		
		this.drawCellCallback(10, 13);
		this.drawCellCallback(10, 14);
		this.drawCellCallback(10, 15);
		this.drawCellCallback(11, 10);
		this.drawCellCallback(11, 11);
		this.drawCellCallback(11, 15);
		this.drawCellCallback(12, 10);
		this.drawCellCallback(12, 11);
		this.drawCellCallback(12, 12);
		this.drawCellCallback(12, 13);
		this.drawCellCallback(12, 14);
		
		this.drawCellCallback(14, 10);
		this.drawCellCallback(14, 11);
		this.drawCellCallback(14, 12);
		this.drawCellCallback(14, 13);
		this.drawCellCallback(14, 14);
		this.drawCellCallback(15, 10);
		this.drawCellCallback(15, 11);
		this.drawCellCallback(15, 15);
		this.drawCellCallback(16, 13);
		this.drawCellCallback(16, 14);
		this.drawCellCallback(16, 15);

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

		/*if (this._changeQueue[2][0] === deathNote.length &&
			this._changeQueue[2][1] === burnNote.length &&
			this._changeQueue[1][0] === deathNote.length &&
			this._changeQueue[1][1] === burnNote.length &&
			this._changeQueue[0][0] === deathNote.length &&
			this._changeQueue[0][1] === burnNote.length
		)
			this.stop();*/

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
	}
}
