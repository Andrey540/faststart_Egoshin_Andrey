function onWindowloaded()
{
    alert('Page loaded');
    var h1element = document.getElementsByTagName('h1');
    var headline = h1element[0];
    headline.innerHTML = 'Hello Sarah!';
    headline.onclick = function()
    {
        onHeadlineClicked(headline);
    }
}

function onHeadlineClicked(headline)
{
    headline.style.color = 'green';
    var link = document.createElement('a');
    link.href = 'http://google.com';
    link.innerHTML = "click me";
    document.body.appendChild(link);
    var helloText = document.getElementById('helloText');
    helloText.innerHTML = '<a href="//ya.ru">Hello, yandex!</a>'
}

window.onload = onWindowloaded;


/*
session_start();


$_SESSION['my_data'] = 'test';

sesseion.destroy







function navigation() {
   var pop = document.getElementById('pop');
   var more = document.getElementById('more');
   var pop1 = document.getElementById('pop1');
   var mote = document.getElementById('mote');
   pop.onmouseover = show;
   more.onmouseover = show;
   
   pop.onmouseout = hide;
   more.onmouseout = hide;
   
   pop1.onmouseover = show1;
   mote.onmouseover = show1;
   
   pop1.onmouseout = hide1;
   mote.onmouseout = hide1;
 
 
}
function show() {
    var menu = document.getElementById('pop');
    var submenu = document.getElementById('more');
    submenu.style.display = 'block';
    submenu.style.width = '149px';
    }
function show1() {
    var sub = document.getElementById('pop1');
    var subm = document.getElementById('mote');
    subm.style.display = 'block';
    subm.style.width = '149px';
}
    
function hide() {
    var menu = document.getElementById('pop');
    var submenu = document.getElementById('more');
    submenu.style.display = 'none';
}
function hide1() {
var sub = document.getElementById('pop1');
var subm = document.getElementById('mote');
subm.style.display = 'none'; 

*/