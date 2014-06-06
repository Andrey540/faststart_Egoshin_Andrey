const TIMEOUT = 20;
const SIZE = 4;
const SQUARE_SIZE = 40;
const STEP = 5;

var divMass = new Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
var isPlaying = true;
var square;
var intervalId = null;
var fromX = 0;
var fromY = 0;
var toX = 0;
var toY = 0;

function indexToX(index)
{
    return (index - 1) % SIZE;
}

function indexToY(index)
{
    var Y = (index - 1) / SIZE;
    return  Y - (Y % 1);
}

function checkMass(digit)
{
    var result = true;
    for (var i = 0; i < divMass.length; i++)
    {
        if (divMass[i] == digit)
        {
            result = false;                
            break;        
        }
    }

    return result;
} 

function setPositionX(square, X)
{
    square.style.left = X + "px";
} 

function setPositionY(square, Y)
{
    square.style.top = Y + "px";
} 

function moveSquareHorizontally()
{
    if (fromX > toX)
    {
        fromX = fromX - STEP;          
    }
    else
    {
        fromX = fromX + STEP;
    }

    setPositionX(square, fromX);
}

function moveSquareVertically()
{
    if (fromY > toY)
    {
        fromY = fromY - STEP;
    }
    else
    {
        fromY = fromY + STEP;
    }   

    setPositionY(square, fromY);
}

function moveSquare()
{
    if (fromX != toX) 
    {
        moveSquareHorizontally();
    }
    else if (fromY != toY) 
    {
        moveSquareVertically();
    }
    else
    {
        clearInterval(intervalId);
        intervalId = null;
    }
}

function checkWin()
{
    var result = true;
    
    for (var i = 0; i < divMass.length; i++)
    {
        if (divMass[i] + 1 != i)
        {
            result = false;
            break;        
        }    
    }
    
    if (result)
        alert('Вы выйграли');
    
    return result;
}

function onClickSquare() //TODO: think and reorganize
{
    if ((isPlaying) && (intervalId == null))
    {
        var id = divMass[parseInt(this.id) - 1];
        var zeroX = indexToX(divMass[SIZE * SIZE - 1]);
        var zeroY = indexToY(divMass[SIZE * SIZE - 1]);
        
        var X = indexToX(id);
        var Y = indexToY(id);
        
        var checkPoints = (zeroX + zeroY) - (X + Y);        

        var canMoveBlock = (((checkPoints == 1) || (checkPoints == -1)) &&
                            ((X == zeroX) || (Y == zeroY)));
        if ( canMoveBlock )
        {             
            divMass[parseInt(this.id) - 1] = divMass[SIZE * SIZE - 1];
            divMass[SIZE * SIZE - 1] = id;
            fromX = X * SQUARE_SIZE;
            fromY = Y * SQUARE_SIZE;
            toX = zeroX * SQUARE_SIZE;
            toY = zeroY * SQUARE_SIZE;
            square = this;
            intervalId = setInterval(moveSquare, TIMEOUT);
        }    
        isPlaying = !checkWin();
    }
}            

function shuffle()
{
    for (var i = 0; i < divMass.length; i++)
    {
        var found = false;
        
        while (!found)
        {
            var x = Math.floor(Math.random() * (SIZE * SIZE + 0.9999));
            
            if (x == 0)
                x = 1;
                
            if (checkMass(x))
            {
                found = true;
                divMass[i] = x; 
            }       
        } 
    } 
}   

function initialize(divs)
{
    var j = 0;
                    
    for (var i = 0; i < divs.length - 1; i++)
    {
        if (divMass[j] == SIZE * SIZE)
            j++;
        divs[i + 1].style.left = SQUARE_SIZE * indexToX(divMass[i]) + "px";
        divs[i + 1].style.top  =  SQUARE_SIZE * indexToY(divMass[i]) + "px";
        divs[i + 1].onclick    = onClickSquare;
        j++;
    }
}          

function onWindowloaded()
{
    var divs = document.getElementsByTagName('div');          

    shuffle();
    initialize(divs); 
}
    
window.onload = onWindowloaded;