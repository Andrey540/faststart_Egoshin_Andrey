    const MAX_WIDTH  = 640;
    const MAX_HEIGHT = 480;
    const CIRCLE_RADIUS = 100;
    const SQUARE_WIDTH  = 180;
    const RECTANGLE_WIDTH  = 150;
    const RECTANGLE_HEIGHT = 200;
    var g_canvas  = null;
    var g_context = null;
    
    var g_circle = {x: -CIRCLE_RADIUS,
                    y: -CIRCLE_RADIUS,
                    radius: CIRCLE_RADIUS}
    
    var g_square = {x: -SQUARE_WIDTH,
                    y: -SQUARE_WIDTH,
                    width: SQUARE_WIDTH,
                    height: SQUARE_WIDTH}
    
    var g_rectangle = {x: -RECTANGLE_WIDTH,
                       y: -RECTANGLE_HEIGHT,
                       width: RECTANGLE_WIDTH,
                       height: RECTANGLE_HEIGHT}
                       
    function compareDistance(x1, y1, x2, y2)
    {
        return Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2) <= CIRCLE_RADIUS * CIRCLE_RADIUS;   
    }
    
    function checkCircleCenter(circle, obj)
    {
        var result = (circle.x >= obj.x) && (circle.x <= obj.x + obj.width);
        result = (result) && ((circle.y >= obj.y) && (circle.y <= obj.y + obj.height));
        
        return result;
    }
    
    function crossSquareSide(circle, obj)
    {
        var result;
        
        if ((circle.x >= obj.x) && (circle.x <= obj.x + obj.width))
        {
            if (circle.y >= obj.y)
            {
                result = compareDistance(circle.x, circle.y, circle.x, obj.y + obj.height);
            }
            else
            {
                result = compareDistance(circle.x, circle.y, circle.x, obj.y);
            }     
        }
        else if ((circle.y >= obj.y) && (circle.y <= obj.y + obj.height))
        {
            if (circle.x >= obj.x)
            {
                result = compareDistance(circle.x, circle.y, obj.x + obj.width, circle.y); 
            }
            else
            {
                result = compareDistance(circle.x, circle.y, obj.x, circle.y); 
            }
        }
        return result;
    }
    
    function crossCircle(circle, obj)
    {
        var result = compareDistance(circle.x, circle.y, obj.x, obj.y);
        result = (result) || (compareDistance(circle.x, circle.y, obj.x + obj.width, obj.y));
        result = (result) || (compareDistance(circle.x, circle.y, obj.x, obj.y + obj.height));
        result = (result) || (compareDistance(circle.x, circle.y, obj.x + obj.width, obj.y + obj.height));
        
        result = (result) || (checkCircleCenter(circle, obj));
        result = (result) || (crossSquareSide(circle, obj));        
        
        return result;    
    }
    
    function crossSquare(obj1, obj2)
    {
        var crossX = ((obj1.x <= obj2.x) && (obj1.x + obj1.width >= obj2.x));
        crossX = (crossX) || ((obj2.x <= obj1.x) && (obj2.x + obj2.width >= obj1.x));
        var crossY = ((obj1.y <= obj2.y) && (obj1.y + obj1.height >= obj2.y));
        crossY = (crossY) || ((obj2.y <= obj1.y) && (obj2.y + obj2.height >= obj1.y));
        
        return ((crossX) && (crossY));    
    }
    
    function generateCircleCoordinates()
    {
        g_circle.x = generateCoordinateX(CIRCLE_RADIUS);
        g_circle.y = generateCoordinateY(CIRCLE_RADIUS);  

        if ((g_circle.x < CIRCLE_RADIUS) || (g_circle.y < CIRCLE_RADIUS))
            generateCircleCoordinates();
    }
    
    function generateSquareCoordinates()
    {
        g_square.x = generateCoordinateX(SQUARE_WIDTH);
        g_square.y = generateCoordinateY(SQUARE_WIDTH); 
        
        if (crossCircle(g_circle, g_square))
        {
            generateSquareCoordinates();
        }    
    }
    
    function generateRectangleCoordinates()
    {
        g_rectangle.x = generateCoordinateX(RECTANGLE_WIDTH);
        g_rectangle.y = generateCoordinateY(RECTANGLE_HEIGHT);
        
        if ((crossCircle(g_circle, g_rectangle)) || (crossSquare(g_square, g_rectangle)))
        {
            generateRectangleCoordinates();
        } 
    
    }      
    
    function initialize()
    {
        g_canvas  = document.getElementById("myCanvas");
        g_context = g_canvas.getContext("2d");       
    }
    
    function generateCoordinateX(size)
    {
        return Math.floor(Math.random() * (MAX_WIDTH + 0.9999 - size));
    }
    
    function generateCoordinateY(size)
    {
        return Math.floor(Math.random() * (MAX_HEIGHT + 0.9999 - size));
    }
    
    function drawCircle(positionX, positionY)
    {
        g_context.beginPath();
        g_context.arc(positionX, positionY, CIRCLE_RADIUS, 0, 2 * Math.PI);   
        g_context.stroke();
        g_context.fillStyle = "red";
        g_context.fill();        
    } 
    
    function drawSquare(positionX, positionY)
    {
        g_context.fillStyle = "green";
        g_context.fillRect(positionX, positionY, SQUARE_WIDTH, SQUARE_WIDTH);       
    }
    
    function drawRectangle(positionX, positionY)
    {
        g_context.fillStyle = "yellow";
        g_context.fillRect(positionX, positionY, RECTANGLE_WIDTH, RECTANGLE_HEIGHT); 
    }
    
    function onWindowloaded()
    {
        initialize();
        generateCircleCoordinates();
        generateSquareCoordinates();
        generateRectangleCoordinates();
        drawCircle(g_circle.x, g_circle.y);
        drawSquare(g_square.x, g_square.y);
        drawRectangle(g_rectangle.x, g_rectangle.y);
    }

    $(onWindowloaded);
    