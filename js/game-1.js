// Лучше сделать много мелких независимых функций, а не объявлять функции в функцие
// в этом лсучае, конечно никуда не деться от глобальных переменных.
// Размер функции не должен быть более 30 строчек.

function Game(elementName, options) {
    var _options = {
        cellAmount: 9
    };
    //----- Конструктор -----
    _init(); // Нижнее подчёткивание лучше не использовать для методов, + лучше не сокращать, лучше - initialize().
    //----------

    {//Cell     // Так я бы тоже не советовал делать.
        /**
         * Создает игровую ячейку
         * @param {number} id
         * Имя HTMLElement
         * @param {number} num
         * Цифра отображаемая на ячейке
         * @param {number} row
         * Номер ряда на игровом поле. Начинается с 0
         * @param {type} col
         * Номер колонки на игровом поле. Начинается с 0
         * @returns {Element}
         */
        function createCell(id, num, row, col) {
            var cell = document.createElement("div");

            cell.setAttribute("class", "cell");
            cell.setAttribute("id", id);
            cell.setAttribute("number", num);
            cell.setAttribute("row", row);
            cell.setAttribute("col", col);
            cell.setAttribute("move", "none");
            cell.style.zIndex = (num === 0) ? 0 : 1;
            cell.style.top = ((row * 100) + "px"); // Если 100 - это размер ячейки, то лучше ввести константу.
            cell.style.left = ((col * 100) + "px");

            var lbl = document.createElement("div");
            lbl.setAttribute("class", "label");
            lbl.innerHTML = (num === 0) ? "" : num;  // "магические" числа лучше не использовать, а объявлять константы, н-р const EMPTY_HTML = 0.

            cell.appendChild(lbl);

            return cell;
        }

        /**
         * Получает ячейку по указанному номеру ряда и столбца
         * @param {number} row
         * Номер ряда ячейки. Первый ряд 0
         * @param {number} col
         * Номер столбца ячейки. Первый столлбец 0
         * @returns {Element}
         */
        function getCellByRowCol(row, col) {
            row = parseInt(row);
            col = parseInt(col);
            var cells = getGame().childNodes;
            for (var i = 0; i < cells.length; i++) {
                if (cells[i].getAttribute("row") == row && cells[i].getAttribute("col") == col) {
                    return cells[i];
                }
            }
        }

        /**
         * Получает ячейку по указанному номеру на ячеке
         * @param {number} number
         * @returns {Element}
         */
        function getCellByNumber(number) {
            number = parseInt(number);

            var cells = getGame().getElementsByClassName("cell");
            for (var i = 0; i < cells.length; i++) {  // Лучше располагать открывающую скобку под закрывающей, так можно добиться лучшего понимания кода.
                if (parseInt(cells[i].getAttribute("number")) === number) {
                    return cells[i];
                }
            }
        }

        /**
         * Задает ячейке указатель на перемещение. Доступны варианты none, up, 
         * down, left, right
         * @param {Element} cell
         * Ячейка
         * @param {string} direction
         */
        function setCellMoveAttr(cell, direction) {
            if (typeof (cell) !== "undefined") {
                var row = getCellAttrs(cell).row;
                var col = getCellAttrs(cell).col;
                cell.setAttribute("row", row);
                cell.setAttribute("col", col);
                cell.setAttribute("move", direction);
            }
        }

        /**
         * Возвращает набор параметров ячеки
         * @param {Element} cell
         * Ячейка
         * @returns {array}
         * Массив из параметров
         */
        function getCellAttrs(cell) {
            var attrs = {
                row: parseInt(cell.getAttribute("row")),
                col: parseInt(cell.getAttribute("col")),
                number: parseInt(cell.getAttribute("number")),
                move: cell.getAttribute("move")
            };
            return attrs;
        }

        /**
         * Устанавливает ячеку в состояние выделения
         * @param {Element} cell
         * Ячейка
         */
        function setCellSelectable(cell) {
            if (typeof (cell) !== "undefined") {
                cell.setAttribute("class", "cell selectable");
            }
        }
    }

    function getGame() {
        return document.getElementById(elementName);
    }


    /**
     * Генерирует массив уникальных случйных числел от 0 до n
     * @param {number} amount 
     * Задает колличесто генерируемых чисел
     * @returns {Array}
     */
    function numberArrayGen(amount) {
        var arr = [];
        while (arr.length < amount) {
            var random_number = Math.ceil(Math.random() * amount - 1);
            var found = false;
            for (var i = 0; i < arr.length; i++) {
                if (arr[i] === random_number) {
                    found = true;
                    break;
                }
            }
            if (!found)
                arr[arr.length] = random_number;
        }
        //arr=[1,2,3,4,5,6,7,0,8];
        return arr;
    }

    function bindEvent(element, event, callback) {
        if (element.addEventListener) {  // Все браузеры за исключением IE версии 9
            element.addEventListener(event, callback, false);
        }
        else {
            if (element.attachEvent) {   // IE до версии 9
                element.attachEvent("on" + event, callback);
            }
        }
    }

    /**
     * Инициализация игры
     */
    function _init() { //initialize
        var el = document.getElementById(elementName);
        if (el) {
            el.setAttribute("class", "field");
        } else {
            throw "[Game] createField: Элемент с именем " + elementName + " не найден";
        }

        optionsLoad();

        
        var row_count = Math.floor(Math.sqrt(_options.cellAmount));
        _options.cellAmount = row_count*row_count;
        var cells = numberArrayGen(_options.cellAmount);

        //размещение элементов по игровому полю
        for (var i = 0; i < cells.length; i++) {
            var row =Math.floor(i / row_count);
            var col =Math.floor(i % row_count);
            var cell = createCell(elementName + "_cell_" + cells[i], cells[i], row, col);
            bindEvent(cell, "click", OnCellClick); // Не понятно зачем делать так, когда можно проще cell.onclick = OnCellClick;.
            el.appendChild(cell);
        }

        statusUpdate();
    }

    {//Options
        /**
         * Загружает значения параметров
         */
        function optionsLoad() {
            if (typeof (options) !== "undefined") {
                optionLoad('cellAmount');
            }
        }

        /**
         * Загружает значения параметров
         * @param {string} name
         */
        function optionLoad(name) {
            if (typeof (options[name]) !== "undefined") {
                _options[name] = options[name];
            }
        }
    }

    {//Status
        function statusUpdate() {
            var nullCell = getCellByNumber(0);
            var row = getCellAttrs(nullCell).row;
            var col = getCellAttrs(nullCell).col;
            //Указать статус для четырех окружающих ячеек
            //Верхняя
            setCellSelectable(getCellByRowCol(row - 1, col));
            setCellMoveAttr(getCellByRowCol(row - 1, col), "down");
            //Нижняя
            setCellSelectable(getCellByRowCol((row + 1), col));
            setCellMoveAttr(getCellByRowCol((row + 1), col), "up");
            //Правая
            setCellSelectable(getCellByRowCol(row, col + 1));
            setCellMoveAttr(getCellByRowCol(row, col + 1), "left");
            //Левая
            setCellSelectable(getCellByRowCol(row, col - 1));
            setCellMoveAttr(getCellByRowCol(row, col - 1), "right");
        }

        /**
         * Cбро состояний для ячеек
         */
        function statusReset() {
            var cells = getGame().getElementsByClassName("cell");
            for (var i = 0; i < cells.length; i++) {
                cells[i].setAttribute("class", "cell");
                cells[i].setAttribute("move", "none");
            }
        }

        /**
         * Проверка расположения ячеек.
         * @returns {Boolean}
         * Возвращает Истина если все числа стоят по порядку
         */
        function statusCheck() {
            var row_count = Math.floor(Math.sqrt(_options.cellAmount));
            for (var i = 0; i < _options.cellAmount - 1; i++) {
                var row = Math.floor(i / row_count);
                var col = Math.floor(i % row_count);

                if (getCellAttrs(getCellByRowCol(row, col)).number !== (i + 1))
                    return false;
            }
            return true;
        }
    }

    /**
     * Функция вызываемая при нажатии на ячейку
     */
    function OnCellClick() {

        var direction = this.getAttribute("move");
        var row = parseInt(this.getAttribute("row"));
        var col = parseInt(this.getAttribute("col"));

        if (direction !== "none") {
            var cell0 = document.getElementById(elementName + "_cell_0");
            cell0.setAttribute("row", row);
            cell0.setAttribute("col", col);
            cell0.style.top = (row) * 100 + "px";
            cell0.style.left = (col) * 100 + "px";
        }
        switch (direction) { // Функция OnCellClick превышает 30 строчек, для перемещения лучще создать функцию moveCell(cell, direction).
            case "down":
                this.setAttribute("row", row + 1);
                this.style.top = (row + 1) * 100 + "px";
                break;
            case "up":
                this.setAttribute("row", row - 1);
                this.style.top = (row - 1) * 100 + "px";
                break;
            case "left":
                this.setAttribute("col", col - 1);
                this.style.left = (col - 1) * 100 + "px";
                break;
            case "right":
                this.setAttribute("col", col + 1);
                this.style.left = (col + 1) * 100 + "px";
                break;
        }
        this.setAttribute("move", "none");

        statusReset();
        if (statusCheck()) {
            alert('GAME OVER!!!\nFOR NEW GAME PRESS F5');
        } else {
            statusUpdate();
        }
    }
}


//----------- Helpers ----------
/*
 * Функция для вывода лог сообщений
 */
function log(msg) {  // Если функция нигде не используется, её лучше убрать.
    var fName = arguments.callee.caller.toString();
    fName = fName.substr('function '.length);
    fName = fName.substr(0, fName.indexOf('('));

    console.log("[" + fName + "] " + msg);
}