<!DOCTYPE html>
<html lang="ru">
<head>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<title>Game of Live</title>
	<link rel="stylesheet" href="css/live.css" type="text/css"/>
	<script type="text/javascript" src="js/live.js"></script>
</head>
<body>
<ul id="choice"> Выбирите тип
  <li>
    <input id="choice1" type="radio" name="answer" value="1">
    <label for="choice1" >Глайдер</label>
  <li>
  <li>
    <input id="choice2" type="radio" name="answer" value="2">
    <label for="choice2" >Госпера</label>
  </li>
  <li>
    <input id="choice3" type="radio" name="answer" value="3">
    <label for="choice3" >Палка</label>
  </li>
  <li>
    <input id="choice4" type="radio" name="answer" value="4">
    <label for="choice4" >Опрокидыватель</label>
  </li>
  <li>
    <input id="choice5" type="radio" name="answer" value="5">
    <label for="choice5" >Чеширский кот</label>
  </li>
</ul>
<input id="start" type="button" name="start" value="start">
<canvas id="viewport" class="hidden"></canvas>
<script>
var bgColor = '#EEE',
	lineColor = '#BBB',
	cellSize = 10;

var canvas = document.getElementById('viewport');
canvas.height = 0.8 * document.body.clientHeight;
canvas.width = 0.8 * document.body.clientWidth;

var context = canvas.getContext('2d');

var topLeft = new Point;
	bottomRight = new Point,
	size = new Point;

function calcOffset()
{
	var hor = canvas.width % cellSize,
		vert = canvas.height % cellSize;

	topLeft.x = Math.round(hor / 2);
	topLeft.y = Math.round(vert / 2);

	bottomRight.x = Math.round(canvas.width - hor / 2);
	bottomRight.y = Math.round(canvas.height - vert / 2);

	size.x = Math.floor(canvas.width / cellSize) - 1,
	size.y = Math.floor(canvas.height / cellSize) - 1;
}
calcOffset();

function drawBackground()
{
	context.fillStyle = lineColor;
	context.fillRect(0, 0, canvas.width, canvas.height);
	context.fillStyle = bgColor;
	context.fillRect(
        topLeft.x,
        topLeft.y,
        bottomRight.x - topLeft.x,
        bottomRight.y - topLeft.y
    );
}
drawBackground();

function drawGreed()
{
	context.strokeStyle = lineColor;
	context.lineWidth = 1;

	context.beginPath();

	for (var i = topLeft.x; i <= bottomRight.x; i += cellSize) {
		context.moveTo(i, topLeft.y);
		context.lineTo(i, bottomRight.y);
	}

	for (var i = topLeft.y; i <= bottomRight.y; i += cellSize) {
		context.moveTo(topLeft.x, i);
		context.lineTo(bottomRight.x, i);
	}

	context.stroke();
}
drawGreed();


function fillCell(x, y, color)
{
	context.fillStyle = color;
	context.fillRect(
		topLeft.x + x * cellSize + 1,
		topLeft.y + y * cellSize + 1,
		cellSize - 2,
		cellSize - 2
	);
}

function startWorld(evt)
{
	var configuration = 0;	
	var radios  = document.getElementsByName("answer");
    for(var k = 0; k < radios.length; k++){
	    if(radios[k].checked){
			configuration = radios[k].value
			break;
	    }
    }

	var world = new World(size.x, size.y, configuration);

	world.drawCellCallback = function(x, y, color)
	{
		fillCell(x, y, color);
	};
	world.eraseCellCallback = function(x, y)
	{
		fillCell(x, y, bgColor);
	};
	
	world.speed = 50;

	world.start();
	
	function canvasClick(evt)
	{
		var x = Math.floor((evt.x - topLeft.x) / cellSize);
		var y = Math.floor((evt.y - topLeft.y) / cellSize);
		world.burnCell(x, y);
	}
	canvas.onclick = canvasClick;

	function keyPress(evt)
	{
		switch (evt.keyCode) {
			case 13: // Enter
				if (world.started)
					world.stop();
				else
					world.start();
				break;

			case 32: // Space
				if (!world.started)
					world.step();
				break;

			case 91: // ]
				world.speed += 50;
				break;

			case 93: // [
				var speed = world.speed - 50;
				if (speed < 50)
					speed = 50;
				world.speed = speed;
				break;

			case 114: // r
				world.stop();
				drawBackground();
				drawGreed();
				world.init(world.size.x, world.size.y);
				world.start();
				break;

			case 99: // c
				world.clear();
				break;
		}
	}
	document.body.onkeypress = keyPress;
}

var startButton = document.getElementById('start');
startButton.onclick = startWorld;

</script>
</body>
</html>