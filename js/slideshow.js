    const TIMEOUT = 3000;
    const HIDE_TIMEOUT = 10;
    const CURSOR_TIMEOUT = 1;
    const FADE_TIMEOUT = 100;
    const SHOW_ARROW = 300;
    const FADE_STEP = 1.5;
    const IMAGE_DIR = "../uploads/";
    const CHANGE_IMAGE = "/slideshow.php";    
    var g_imageNumber = 0;    
    var g_mainSize = 0;
    var g_position = 0;
    var $g_img  = null;    
    var $g_next = null;
    var $g_prev = null;
    var g_image = null;
    var $g_imgFirst  = null;
    var $g_imgSecond = null;
    var g_intervalImage = null;
    var g_intervalCursor = null;
    var g_timeoutFade = null;
    var g_showArrowLeft = false;
    var g_showArrowRight = false; 
    var g_dataSended = false;
    var g_opacity = FADE_TIMEOUT;    
    
    function fadeToNext()
    {
        g_opacity -= FADE_STEP;
        $g_imgFirst.css({opacity: g_opacity / FADE_TIMEOUT});
        $g_imgSecond.css({opacity: (FADE_TIMEOUT - g_opacity) / FADE_TIMEOUT});
        g_timeoutFade = setTimeout("fade_to_next()", 1);
        if ((g_opacity <= 0) || (g_dataSended))
        {
            g_opacity = FADE_TIMEOUT;
            clearTimeout(g_timeoutFade);
            var replace = $g_imgFirst;
            $g_imgFirst = $g_imgSecond;
            $g_imgSecond = replace;
        }
    }
        
    function showImage()
    {        
        $g_imgFirst.css({opacity: 1.0});
        $g_imgSecond.css({opacity: 1.0});
        $g_imgSecond.attr("src", IMAGE_DIR + g_image.file_id + "." + g_image.extension);
        fadeToNext();        
    }
     
    function onChangeImage(response)
    {
        g_image = response.image;
        g_imageNumber = response.number;
        g_dataSended = false;
        showImage();       
    } 
    
    function sendData()
    {
        g_dataSended = true;
        g_imageNumber++;
        var data = {image: g_imageNumber};
        $.post(CHANGE_IMAGE, data, onChangeImage, 'json');
    }
    
    function onImageClick()
    {
        if (g_position < (g_mainSize / 2))
        {
            g_imageNumber = g_imageNumber - 2;
        }
            
        clearInterval(g_intervalImage);     
        sendData();
        g_intervalImage = setInterval(sendData, TIMEOUT);      
    }
    
    function checkCursor()
    {
        if (g_position >= (g_mainSize / 2))
        {
            $g_next.show(SHOW_ARROW);
            g_showArrowLeft = true;
            g_showArrowRight = false;
            setTimeout(hideArrowRight, HIDE_TIMEOUT);
        }
        else
        {
            $g_prev.show(SHOW_ARROW);
            g_showArrowRight = true;
            g_showArrowLeft = false;
            setTimeout(hideArrowLeft, HIDE_TIMEOUT);
        }       
    }
    
    function onMouseover()
    {
        if ((!g_showArrowLeft) && (!g_showArrowRight) && (g_intervalCursor == null))
        {
            g_intervalCursor = setInterval(checkCursor, CURSOR_TIMEOUT);
        }
    }
    
    function hideAll()
    {
        if ((!g_showArrowLeft) && (!g_showArrowRight))
        {
            setTimeout(hideArrowLeft, HIDE_TIMEOUT);
            setTimeout(hideArrowRight, HIDE_TIMEOUT);
        }
    }
    
    function onMouseout()
    {
        g_showArrowLeft = false;
        g_showArrowRight = false;
        clearInterval(g_intervalCursor);
        g_intervalCursor = null;
        setTimeout(hideAll, HIDE_TIMEOUT);
    }
    
    function hideArrowLeft()
    {
        if (!g_showArrowLeft)
        {
            $g_next.hide(SHOW_ARROW);
        }
    }
    
    function hideArrowRight()
    {
        if (!g_showArrowRight)
        {
            $g_prev.hide(SHOW_ARROW);
        }
    }
    
    function onMouseoverArrowLeft()
    {
        g_showArrowLeft = true;    
    }
    
    function onMouseoverArrowRight()
    {
        g_showArrowRight = true;    
    }
    
    function onMouseoutArrowLeft()
    {
        g_showArrowLeft = false;   
        setTimeout(hideArrowLeft, HIDE_TIMEOUT);        
    }
    
    function onMouseoutArrowRight()
    {
        g_showArrowRight = false;  
        setTimeout(hideArrowRight, HIDE_TIMEOUT);        
    }
    
    function onMouseMove()
    {
        g_position = event.pageX;
    }
    
    function initialize()
    {
        g_mainSize = $(".main_block").width();
        sendData();
        g_intervalImage = setInterval(sendData, TIMEOUT);
        $g_imgFirst = $("#img_first");
        $g_imgSecond = $("#img_second");
        $g_img = $("img");
        $g_next = $("#next");
        $g_prev = $("#prev");
        $g_img.bind('mouseover', onMouseover);
        $g_img.bind('mouseout', onMouseout);
        $g_img.bind('click', onImageClick);   
        $g_next.bind('click', onImageClick); 
        $g_prev.bind('click', onImageClick);         
        $g_next.bind('mouseover', onMouseoverArrowLeft);
        $g_prev.bind('mouseover', onMouseoverArrowRight);
        $g_next.bind('mouseout', onMouseoutArrowLeft);
        $g_prev.bind('mouseout', onMouseoutArrowRight);
        $g_img.bind('mousemove', onMouseMove);    
    }
    
    function onWindowloaded()
    {
        initialize();
    }

    $(onWindowloaded);
    