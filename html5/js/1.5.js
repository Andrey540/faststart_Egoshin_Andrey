    const MAX_WIDTH  = 640;
    const MAX_HEIGHT = 480;
    const CIRCLE_RADIUS = 50;
    const STEP_BACK = 10;        // Шаг разведения шарика с объектом
    const SPEED = 5;
    const MAX_COEFFICIENT = 0.2; // Коэффициент для заужения угла полёта шарика.
    var g_canvas  = null;
    var g_context = null;
    
    var g_circle1 = {x: CIRCLE_RADIUS + 1,
                     y: MAX_HEIGHT / 2,
                     dx: 0,
                     dy: 0,
                     radius: CIRCLE_RADIUS}
                     
    var g_circle2 = {x: MAX_WIDTH - CIRCLE_RADIUS - 1,
                     y: MAX_HEIGHT / 2,
                     dx: 0,
                     dy: 0,
                     radius: CIRCLE_RADIUS}
                       
    function compareDistance(x1, y1, x2, y2)
    {
        return Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2) <= CIRCLE_RADIUS * CIRCLE_RADIUS * 4;   
    }
    
    // Движение шарика
    function moveCircles(circle)
    {
        circle.x += circle.dx;
        circle.y += circle.dy;               
    }   
    
    // Отводим шарик от стенки при ударе.
    function moveFromBord(circle)
    {
        while(crossBordX(circle) || crossBordY(circle))
        {
            circle.x += circle.dx / STEP_BACK;
            circle.y += circle.dy / STEP_BACK;        
        }    
    }

    // Отводим шарики друг от друга.
    function moveBackCircles(circle1, circle2)
    {
        var dist = Math.sqrt(Math.pow((circle1.x - circle2.x), 2) + Math.pow((circle1.y - circle2.y), 2));
        var a = circle1.x - circle2.x;
        var b = circle1.y - circle2.y;
        var cosA = a / dist;
        var sinA = b / dist;        
        var vect = (CIRCLE_RADIUS * 2 - dist);
        
        circle1.x += vect * cosA;
        circle1.y += vect * sinA;
        circle2.x -= vect * cosA;
        circle2.y -= vect * sinA;  
    }
    
    // Столкновение с вертикальными стенкками.
    function crossBordX(circle)
    {
        return ((circle.x <= CIRCLE_RADIUS) || (circle.x >= MAX_WIDTH - CIRCLE_RADIUS));
    }
    
    // Столкновение с горизонтальными стенками.
    function crossBordY(circle)
    {
        return ((circle.y <= CIRCLE_RADIUS) || (circle.y >= MAX_HEIGHT - CIRCLE_RADIUS));
    }
    
    // Отводит шарик от вертикальныч стенок.
    function moveFromBordX(circle)
    {
        if (circle.x < CIRCLE_RADIUS)
        {
            circle.x += CIRCLE_RADIUS - circle.x;
        }
        else if (circle.x > MAX_WIDTH - CIRCLE_RADIUS)
        {
            circle.x += MAX_WIDTH - CIRCLE_RADIUS - circle.x;
        }
    }
    
    // Отводит шарик от горизонтальных стенок.
    function moveFromBordY(circle)
    {
        if (circle.y < CIRCLE_RADIUS)
        {
            circle.y += CIRCLE_RADIUS - circle.y;
        }
        else if (circle.y > MAX_HEIGHT - CIRCLE_RADIUS)
        {
            circle.y += MAX_HEIGHT - CIRCLE_RADIUS - circle.y;
        }
    }
    
    // Анализирует столкновение шарика со стенкой.
    function checkPositionBord(circle)
    {
        if (crossBordX(circle))
        {
            circle.dx = -circle.dx;
            circle.x += circle.dx;   
            moveFromBordX(circle);                        
        }
        if (crossBordY(circle))
        {
            circle.dy = -circle.dy;  
            circle.y += circle.dy;
            moveFromBordY(circle);
        }
    }
    
    // Изменяет вектора столкнувшихся шариков
    function changeVector(circle1, circle2)
    {
        var dist = Math.sqrt(Math.pow((circle1.x - circle2.x), 2) + Math.pow((circle1.y - circle2.y), 2));
        
        if (dist < CIRCLE_RADIUS * 2)
        {
            var a = circle1.x - circle2.x;
            var b = circle1.y - circle2.y;
            var sinAcosA = (a * b) / Math.pow(dist, 2);
            var cosA = a / dist;
            var sinA = b / dist;
            var deltaX = circle1.dy * sinAcosA + circle1.dx * Math.pow(cosA, 2) - 
                        circle2.dy * sinAcosA - circle2.dx * Math.pow(cosA, 2);
                     
            var deltaY = circle1.dx * sinAcosA + circle1.dy * Math.pow(sinA, 2) - 
                        circle2.dx * sinAcosA - circle2.dy * Math.pow(sinA, 2);
                     
            circle1.dx -= deltaX;
            circle1.dy -= deltaY;
            circle2.dx += deltaX;
            circle2.dy += deltaY;
            moveBackCircles(circle1, circle2);
        }
    }   
    
    // Анализирует столкновения шариков.
    function checkPosition()
    {
        checkPositionBord(g_circle1);
        checkPositionBord(g_circle2);
        
        if (compareDistance(g_circle1.x, g_circle1.y, g_circle2.x, g_circle2.y))
        {
            changeVector(g_circle1, g_circle2);
        }
    }
    
    // Шаг программы
    function drawFrame()
    {
        window.requestAnimationFrame(drawFrame, g_canvas);
        g_context.clearRect(0, 0, MAX_WIDTH, MAX_HEIGHT); 
        checkPosition();
        moveCircles(g_circle1);
        moveCircles(g_circle2);
        drawCircle(g_circle1); 
        drawCircle(g_circle2);   
    }
    
    // Инициализирует канву.
    function initialize()
    {
        g_canvas  = document.getElementById("myCanvas");
        g_context = g_canvas.getContext("2d");       
    }
    
    // Создаёт вектора движения двух шариков,
    // летящих на встречу друг другу.     
    function generateVector()
    {
        var angel = Math.random() * MAX_COEFFICIENT;
        angel = (angel == 0) ? MAX_COEFFICIENT : angel;
        angel = (Math.random() > 0.5) ? angel : angel * -1;
        
        g_circle1.dx = SPEED * Math.cos(angel);
        g_circle1.dy = SPEED * Math.sin(angel);        
        
        angel = Math.random() * MAX_COEFFICIENT;
        angel = (angel == 0) ? MAX_COEFFICIENT : angel;
        angel = (Math.random() > 0.5) ? angel : angel * -1;
        angel += Math.PI;
        
        g_circle2.dx = SPEED * Math.cos(angel);
        g_circle2.dy = SPEED * Math.sin(angel);       
    }
    
    // Инициализирует шараки.
    function initializeCircles()
    {
        generateVector();    
    }
    
    // Отрисовка шарика.
    function drawCircle(circle)
    {
        g_context.beginPath();
        g_context.arc(circle.x, circle.y, CIRCLE_RADIUS, 0, 2 * Math.PI);   
        g_context.stroke();
        g_context.fillStyle = "red";
        g_context.fill();        
    } 
    
    function onWindowloaded()
    {
        initialize();
        initializeCircles();        
        drawFrame();
    }

    window.onload = onWindowloaded;
    