    var media = null;
    
    function onClickPlay()
    {
        media.play();
    }
    
    function onClickPause()
    {
        media.pause();
    }
    
    function onWindowloaded()
    {        
        media = document.getElementById("media");
        $(".play").bind('click', onClickPlay);
        $(".pause").bind('click', onClickPause);
    }
    
    $(onWindowloaded);    