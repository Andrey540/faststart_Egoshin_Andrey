    const MAX_WIDTH  = 640;
    const MAX_HEIGHT = 480;
    const CIRCLE_RADIUS = 100;
    const SPEED = 5;
    const MAX_COEFFICIENT = 2;
    var g_canvas  = null;
    var g_context = null;
    
    var g_circle = {x: -CIRCLE_RADIUS,
                    y: -CIRCLE_RADIUS,
                    k: 0,
                    side: 1,
                    radius: CIRCLE_RADIUS}
                       
    function compareDistance(x1, y1, x2, y2)
    {
        return Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2) <= CIRCLE_RADIUS * CIRCLE_RADIUS;   
    }
    
    function moveCircle()
    {
        g_circle.x += SPEED * g_circle.side;
        g_circle.y += g_circle.k * SPEED;
    }
    
    function checkPosition()
    {
        if ((g_circle.x <= CIRCLE_RADIUS) || (g_circle.x >= MAX_WIDTH - CIRCLE_RADIUS))
        {
            g_circle.side *= -1;        
        }
        if ((g_circle.y <= CIRCLE_RADIUS) || (g_circle.y >= MAX_HEIGHT - CIRCLE_RADIUS))
        {
            g_circle.k *= -1;      
        }    
    }
    
    function drawFrame()
    {
        window.requestAnimationFrame(drawFrame, g_canvas);
        g_context.clearRect(0, 0, MAX_WIDTH, MAX_HEIGHT);  
        checkPosition();
        moveCircle();
        drawCircle(g_circle.x, g_circle.y);                        
    }
    
    function generateCircleCoordinates()
    {
        g_circle.x = generateCoordinateX(CIRCLE_RADIUS);
        g_circle.y = generateCoordinateY(CIRCLE_RADIUS);  

        while ((g_circle.x < CIRCLE_RADIUS) || (g_circle.y < CIRCLE_RADIUS))
        {
            g_circle.x = generateCoordinateX(CIRCLE_RADIUS);
            g_circle.y = generateCoordinateY(CIRCLE_RADIUS);
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
    
    function generateVector()
    {
        g_circle.k = Math.random() * MAX_COEFFICIENT;
        g_circle.k = (g_circle.k == 0) ? 1 : g_circle.k;
        g_circle.k = (Math.random() > 0.5) ? g_circle.k : g_circle.k * -1;
        g_circle.side = (Math.random() > 0.5) ? 1 : -1;
    }
    
    function initializeCircle()
    {
        generateCircleCoordinates();
        generateVector();    
    }
    
    function drawCircle(positionX, positionY)
    {
        g_context.beginPath();
        g_context.arc(positionX, positionY, CIRCLE_RADIUS, 0, 2 * Math.PI);   
        g_context.stroke();
        g_context.fillStyle = "red";
        g_context.fill();        
    } 
    
    function onWindowloaded()
    {
        initialize();
        initializeCircle();        
        drawFrame();
    }

    $(onWindowloaded);
    