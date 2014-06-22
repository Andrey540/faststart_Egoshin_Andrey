    function checkName(name)
    {
        const MIN_NAME_LENGTH = 3;
        result = true;
        
        if ((name.length < MIN_NAME_LENGTH) || ((name[0] < 'A') || (name[0] > 'Z')))
        {
            result = false;
        }
        else
        {
            for (var i = 1; i < name.length; i++)
            {
                if ((name[i] < 'a') || (name[i] > 'z'))
                {
                    result = false;
                    break;
                }            
            }
        }    
    
        return result;
    }
    
    function checkEmail(email)
    {
        var result = true;
        email.toLowerCase();
        var dog = email.indexOf('@', 0);
        var dot = email.indexOf('.', 0);
        
        if ((dog == 0) || (dot == 0) || (dog > dot))
        {
            result = false;
        }
        else
        {            
            for (i = 0; i < dog; i++)
            {
                if (((email[i] < 'a') || (email[i] > 'z')) && ((email[i] < '0') || (email[i] > '9')))
                {
                    result = false;
                    break;
                }	  
            }
	  
            for (i = dog + 1; i < email.length; i++)
            {
                if ((i != dot) && ((email[i] < 'a') || (email[i] > 'z')))
                {
                    result = false;
                    break;
                }	  
            }
        }
    
        return result;
    }

    function checkPassword(pass)
    {
        const MIN_PASSWORD_LENGTH = 6;
        var result = true;
        
        if (pass.length < MIN_PASSWORD_LENGTH)
            result = false;    
    
        return result;
    }

    function onSubmit()
    {
        var result = true;
        var inputs = document.getElementsByTagName('input');
        var selects = document.getElementsByTagName('select');
        
        if (!checkName(inputs[0].value))
        {
            result = false;
            alert("Wrong parameter 'First Name'!");
        }
        else if (!checkName(inputs[1].value))
        {
            result = false;
            alert("Wrong parameter 'Last Name'!");        
        }
        else if (inputs[2].value != inputs[3].value)
        {
            result = false;
            alert("Wrong not equal emails!");        
        }
        else if (!checkEmail(inputs[2].value))
        {
            result = false;
            alert("Wrong parameter 'Email'!");        
        }
        else if (!checkPassword(inputs[4].value))
        {
            result = false;
            alert("Wrong password length!");        
        }
        else if (selects[0].value == "0")
        {
            result = false;
            alert("Wrong parameter 'Sex'!");        
        }        
        else if (selects[1].value == "0")
        {
            result = false;
            alert("Wrong parameter 'Month'!");            
        }
        else if (selects[2].value == "0")
        {
            result = false;
            alert("Wrong parameter 'Day'!");        
        }
        else if (selects[3].value == "0")
        {
            result = false;
            alert("Wrong parameter 'Yaer'!");        
        }
        
        return result;    
    }
    
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
    
    function onPasswordStrengthCheck(response, headers)
    {
        var checkResult = document.getElementById('check_result');
        
        switch (response)
        {
            case '0':
                checkResult.innerHTML   = 'weak';
                checkResult.style.color = 'red';
                break;
            case '1':
                checkResult.innerHTML   = 'good';
                checkResult.style.color = 'yellow';
                break;
            case '2':
                checkResult.innerHTML   = 'strong';
                checkResult.style.color = 'green';
                break;
        }               
    }
    
    function onChange()
    {
        var password = document.getElementsByName('password');
        var PASSWORD_STRENGTH_URL = "/password_strength.php";
        var data = "password=" + encodeURIComponent(password[0].value);
        
        getUrl(PASSWORD_STRENGTH_URL, onPasswordStrengthCheck, data);
    } 

function trySelectors()
{
    $("h1").css({background: "green"});

}    
    
    function onWindowloaded()
    {
     //   trySelectors();
        var elements = document.getElementsByTagName('form');
        var form = elements[0];
        form.onsubmit = onSubmit;
        
        var password = document.getElementsByName('password');
        password[0].onchange = onChange;            
    }
    
   // window.onload = onWindowloaded;
    $(onWindowloaded);
    