    const MAX_WIDTH  = 640;
    const MAX_HEIGHT = 480;
    const CIRCLE_RADIUS = 20;
    const SPEED = 10;               // Коэффициент скорости шарика.
    const MAX_COEFFICIENT = 5;      // Добавочный коэффициент угла полёта шарика.
    const START_COUNT = 10;         // Начальное количество шаров.
    const TRY_CREATE_CIRCLE = 100;  // Количество попыток создания нового шарика.
    var g_canvas  = null;
    var g_context = null;
    var g_circles = new Array();    // Массив шаров.
    var g_countCircles = 0;        
    
    // Создаёт новый шар.
    function createCircle()
    {
        var circle = {x: 0,
                      y: 0,
                     dx: 0,
                     dy: 0,
                     radius: CIRCLE_RADIUS}

        if(initializeCircle(circle) == 0)
        {        
            g_countCircles++;
        }
        else
        {
            circle = g_circles[g_countCircles - 1];
            alert("Не удалось создать объект");
        }
        
        return circle;
    }
    
    // Вычисляет расстояние между точками
    function compareDistance(x1, y1, x2, y2)
    {
        return Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2) <= CIRCLE_RADIUS * CIRCLE_RADIUS * 4;   
    }
    
    // Движение шаров
    function moveCircles()
    {
        for (var i = 0; i < g_circles.length; i++)
        {
            var x = g_circles[i].x + g_circles[i].dx;
            var y = g_circles[i].y + g_circles[i].dy;            

            g_circles[i].x += g_circles[i].dx;
            g_circles[i].y += g_circles[i].dy;                                      
        }
    }   
        
    // Отводит шарики друг от друга.
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
    
    // Проверка столкновения с вертикальными стенкками.
    function crossBordX(circle)
    {
        return ((circle.x <= CIRCLE_RADIUS) || (circle.x >= MAX_WIDTH - CIRCLE_RADIUS));
    }
    
    // Проверка столкновения с горизонтальными стенками.
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
            circle.x -= MAX_WIDTH - CIRCLE_RADIUS - circle.x;
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
            circle.y -= MAX_HEIGHT - CIRCLE_RADIUS - circle.y;
        }
    }
    
    // Анализирует столкновение шарика со стенкой.
    function checkPositionBord()
    {
        for (var i = 0; i < g_circles.length; i++)
        {
            if (crossBordX(g_circles[i]))
            {
                g_circles[i].dx = -g_circles[i].dx;
                g_circles[i].x += g_circles[i].dx;   
                moveFromBordX(g_circles[i]);                        
            }
            if (crossBordY(g_circles[i]))
            {
                g_circles[i].dy = -g_circles[i].dy;  
                g_circles[i].y += g_circles[i].dy;
                moveFromBordY(g_circles[i]);
            }
        }
    }
    
    // Анализирует столкновения шариков между собой.
    function checkPositionCollises()
    {
        for (var i = 0; i < g_circles.length; i++)
        {
            for (j = 0; j < g_circles.length; j++)
            {
                if (i != j)
                {
                    if (compareDistance(g_circles[i].x, g_circles[i].y, g_circles[j].x, g_circles[j].y))
                    {                        
                        changeVector(g_circles[i], g_circles[j]);
                    }
                }
            }
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
            var cosA = a / dist;
            var sinA = b / dist;
        
            var deltaX = circle1.dy * (sinA * cosA) + circle1.dx * (cosA * cosA) - 
                        circle2.dy * (sinA * cosA) - circle2.dx * (cosA * cosA);
                     
            var deltaY = circle1.dx * (sinA * cosA) + circle1.dy * (sinA * sinA) - 
                        circle2.dx * (sinA * cosA) - circle2.dy * (sinA * sinA);        
                     
            circle1.dx -= deltaX;
            circle1.dy -= deltaY;
            circle2.dx += deltaX;
            circle2.dy += deltaY;
        
            moveBackCircles(circle1, circle2);
        }        
    }   
    
    // Анализирует столкновения шариков.
    function checkPositions()
    {     
        checkPositionCollises();
        checkPositionBord();
    }
    
    // Шаг программы
    function drawFrame()
    {
        window.requestAnimationFrame(drawFrame, g_canvas);
        g_context.clearRect(0, 0, MAX_WIDTH, MAX_HEIGHT); 
        checkPositions();
        moveCircles();
        drawCircles(); 
    }
    
    // Инициализирует канву.
    function initialize()
    {
        g_canvas  = document.getElementById("myCanvas");
        g_context = g_canvas.getContext("2d");
        var add    = document.getElementById("add");
        var remove = document.getElementById("remove"); 
        add.onclick    = addCircle;
        remove.onclick = removeCircle;
    }
    
    // Добавляет новый шарик.
    function addCircle()
    {
        g_circles[g_countCircles] = createCircle();
    }
    
    // Удаляет шарик.
    function removeCircle()
    {
        if (g_countCircles > 0)
        {
            g_circles.pop();
            g_countCircles--;
        }
    }
    
    // Создаёт вектора движения двух шариков,
    // летящих на встречу друг другу.     
    function generateVector(circle)
    {
        var angel = Math.random() * MAX_COEFFICIENT;
        angel = (angel == 0) ? MAX_COEFFICIENT : angel;
        angel = (Math.random() > 0.5) ? angel : angel * -1;
        var speed = Math.random() * SPEED;
        
        circle.dx = speed * Math.cos(angel);
        circle.dy = speed * Math.sin(angel);              
    }
    
    // Генерирует координату X.
    function generateCoordinateX(circle)
    {
        circle.x = Math.floor(Math.random() * MAX_WIDTH - CIRCLE_RADIUS - 1);
        
        while (crossBordX(circle))
        {
            circle.x = Math.floor(Math.random() * MAX_WIDTH - CIRCLE_RADIUS - 1);
        }
    }
    
    // Генерирует координату Y.
    function generateCoordinateY(circle)
    {
        circle.y = Math.floor(Math.random() * MAX_HEIGHT - CIRCLE_RADIUS - 1);
        
        while (crossBordY(circle))
        {
            circle.y = Math.floor(Math.random() * MAX_HEIGHT - CIRCLE_RADIUS - 1);
        }
    }
    
    // Преверяет пересекается ли шарик с другими.
    function checkCrossingCircles(circle)
    {
        var result = false;
        
        for (var i = 0; i < g_circles.length; i++)
        {
            if (compareDistance(circle.x, circle.y, g_circles[i].x, g_circles[i].y))
            {
                result = true;
                break;            
            }        
        }
        return result;
    }
    
    // Инициализация координат шарика.
    function generateCoordinates(circle)
    {
        var error = 0;
        generateCoordinateX(circle);
        generateCoordinateY(circle);
        
        var count = 0;
        while(checkCrossingCircles(circle))
        {
            if (count > TRY_CREATE_CIRCLE)
            {
                error = -1;
            }            
            generateCoordinateX(circle);
            generateCoordinateY(circle);            
            count++;
        }
        
        return error;
    }
    
    // Инициализирует шараки.
    function initializeCircle(circle)
    {
        generateVector(circle); 
        return generateCoordinates(circle);       
    }
    
    // Отрисовка шарика.
    function drawCircles(circle)
    {
        for (var i = 0; i < g_circles.length; i++)
        {
            g_context.beginPath();
            g_context.arc(g_circles[i].x, g_circles[i].y, CIRCLE_RADIUS, 0, 2 * Math.PI);   
            g_context.stroke();
            g_context.fillStyle = "green";
            g_context.fill();   
        }
    } 
    
    // Создание шариков по-умолчанию
    function createCircles()
    {
        for (var i = 0; i < START_COUNT; i ++)
        {
            g_circles[g_countCircles] = createCircle();
        }    
    }
    
    function onWindowloaded()
    {
        initialize();
        createCircles();              
        drawFrame();
    }

    window.onload = onWindowloaded;
    