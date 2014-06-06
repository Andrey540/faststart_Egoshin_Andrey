    var showSubMenu = true;
    const TIME_OUT = 100;
    
    function lock()
    {
        showSubMenu = false;
    }     
    
    function hideHome()
    {
        if (showSubMenu)
        {
            var home = document.getElementById('block_home');
            home.style.display = 'none';
        }  
    }
    
    function hideProducts()
    {
        if (showSubMenu)
        {
            var products = document.getElementById('block_products');
            products.style.display = 'none';
        }  
    }
    
    var menu_home      = document.getElementById('menu_home');
    var block_home     = document.getElementById('block_home');
    var menu_products  = document.getElementById('menu_products');
    var block_products = document.getElementById('block_products');
    
    // определение обработчиков событии блока Home
    menu_home.onmouseover = function()
    {
        if (showSubMenu)
            block_home.style.display = 'block';
    };
    
    menu_home.onmouseout  = function()
    {
        setTimeout(hideHome, TIME_OUT);
    };    
    
    // определение обработчиков событии подменю блока Home
    block_home.onmouseover = lock;
    block_home.onmouseout  =  function()
    {
        showSubMenu = true;
        setTimeout(hideHome, TIME_OUT);
    };
    
    // определение обработчиков событии блока Products
    menu_products.onmouseover = function()
    {
        if (showSubMenu)
            block_products.style.display = 'block';
    };
    
    menu_products.onmouseout  = function()
    {
        setTimeout(hideProducts, TIME_OUT);
    };    
    
    // определение обработчиков событии подменю блока Products
    block_products.onmouseover = lock;
    block_products.onmouseout  =  function()
    {
        showSubMenu = true;
        setTimeout(hideProducts, TIME_OUT);
    };