    const MAX_WIDTH  = 640;
    const MAX_HEIGHT = 480;
    const MAIN_CIRCLE_RADIUS = 80;
    const SPIN_CIRCLE_RADIUS = 10;
    const SPIN_RADIUS = 200;
    const MAIN_CIRCLE_X = MAX_WIDTH / 2;
    const MAIN_CIRCLE_Y = MAX_HEIGHT / 2;
    const FPS = 34;
    const SPEED = 1;

    var g_canvas  = null;
    var g_context = null;
    var g_angel = 0;
                       
    function compareDistance(x1, y1, x2, y2)
    {
        return Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2) <= CIRCLE_RADIUS * CIRCLE_RADIUS;   
    }
    
    function spinCircle()
    {
        if (g_angel == 360)
        {
            g_angel = 0;
        }
      
        var x = SPIN_RADIUS * Math.cos(g_angel / 180 * Math.PI) + MAIN_CIRCLE_X;
        var y = SPIN_RADIUS * Math.sin(g_angel / 180 * Math.PI) + MAIN_CIRCLE_Y;
        
        drawSpinCircle(x, y);
        
        g_angel++;
    }    
    
    function step()
    {
        setTimeout(function()
                  {
                        requestAnimationFrame(step);
                        g_context.clearRect(0, 0, MAX_WIDTH, MAX_HEIGHT);  
                        drawMainCircle();
                        spinCircle();
                        // Drawing code goes here
                  }, FPS);
    }
        
    function initialize()
    {
        g_canvas  = document.getElementById("myCanvas");
        g_context = g_canvas.getContext("2d");       
    }    
        
    function drawSpinCircle(positionX, positionY)
    {
        g_context.beginPath();
        g_context.arc(positionX, positionY, SPIN_CIRCLE_RADIUS, 0, 2 * Math.PI);   
        g_context.stroke();
        g_context.fillStyle = "red";
        g_context.fill();        
    } 
    
    function drawMainCircle()
    {
        g_context.beginPath();
        g_context.arc(MAIN_CIRCLE_X, MAIN_CIRCLE_Y, MAIN_CIRCLE_RADIUS, 0, 2 * Math.PI);   
        g_context.stroke();
        g_context.fillStyle = "red";
        g_context.fill();        
    }
    
    function onWindowloaded()
    {
        initialize();  
        step();
    }

    $(onWindowloaded);
    