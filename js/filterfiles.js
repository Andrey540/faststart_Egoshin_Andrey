    const rateValue = "value";
    var g_busy = false;
    
    function getXmlHttp()
    {
        var xhr = false;
        try
        {
            xhr = new ActiveXObject("Msxml2.XMLHTTP");        
        }
        catch(e)
        {
            try
            {
                xhr = new ActiveXObject("Microsoft.XMLHTTP");            
            }
            catch(e)
            {
                // do nothing.
            }        
        }    
        
        if (typeof XMLHttpRequest != 'undefined')
        {
            xhr = new XMLHttpRequest();
        }
        
        return xhr;
    }
    
    function getUrl(url, callback, data)
    {
        var xhr = getXmlHttp();
        if (!xhr)
        {
            return;             
        }
        
        var async = true;
        xhr.open("POST", url, async);
        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        xhr.onreadystatechange = function()
        {
            if ((xhr.readyState == 4) && (xhr.status == 200))
            {
                callback(xhr.responseText, xhr.getAllResponseHeaders());           
            }                    
        };
        xhr.send(data);   
    }
    
    function onChangeRate(response, headers)
    {
        var  answer = JSON.parse(response);
        var file = takeLiBlock(answer.file_id); 
        var user = file.parentElement;         
        var value = takeRateBlock(file);
        value.innerHTML = answer.rate;
        g_busy = false;
    }
    
    function takeRateBlock(list)
    {
        var value = null;
        var divs = list.getElementsByTagName('div');
        
        for (var i = 0; i < divs.length; i++)
        {
            if (divs[i].className == rateValue)
            {
                value = divs[i];
                break;
            }
        } 
        
        return value;
    }
    
    function takeLiBlock(id)
    {
        var value = null;
        var lis = document.getElementsByTagName('li');
        
        for (var i = 0; i < lis.length; i++)
        {
            if (lis[i].id == id)
            {
                value = lis[i];
                break;
            }
        } 
        
        return value;
    }
    
    function onClickIncrement()
    {
        if (!g_busy)
        {
            g_busy = true;
            var file = this.parentElement; 
            var user = file.parentElement;         
            var CHANGE_RATE_URL = "/change_rate.php";
            var value = takeRateBlock(file);
            var data = "file_id=" + file.id + "&user_id=" + user.id + '&rate=' + value.innerHTML + '&action=1';
        
            getUrl(CHANGE_RATE_URL, onChangeRate, data);
        }
    }
    
    function onClickDecrement()
    {
        if (!g_busy)
        {
            g_busy = true;
            var file = this.parentElement; 
            var user = file.parentElement;         
            var CHANGE_RATE_URL = "/change_rate.php";
            var value = takeRateBlock(file);
            var data = "file_id=" + file.id + "&user_id=" + user.id + '&rate=' + value.innerHTML + '&action=-1';

            getUrl(CHANGE_RATE_URL, onChangeRate, data);
        }        
    }
    
    function addHrefs()
    {        
        $(".file > a").each(function(aElement)
        {
            var str = $(this).text();
            var id = $(this).parent().parent().attr('id');
            
            if (str.indexOf('.mp3') != -1)
            {
                $(this).attr("href", '/formmedia.php?audio=' + id + '.mp3');
            }
            else if (str.indexOf('.mp4') != -1)
            {
                $(this).attr("href", '/formmedia.php?video=' + id + '.mp4');
            }
        }); 
    }
    
    function onWindowloaded()
    {        
        addHrefs();
        
        var increments = document.getElementsByName('increment');
        
        for (var i = 0; i < increments.length; i++)
        {
            increments[i].onclick = onClickIncrement;
        } 

        var decrements = document.getElementsByName('decrement');
        
        for (var i = 0; i < decrements.length; i++)
        {
            decrements[i].onclick = onClickDecrement;
        }         
    }
    
    $(onWindowloaded);    