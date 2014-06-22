// ����� ������� ����� ������ ����������� �������, � �� ��������� ������� � �������
// � ���� ������, ������� ������ �� ������ �� ���������� ����������.
// ������ ������� �� ������ ���� ����� 30 �������.

function Game(elementName, options) {
    var _options = {
        cellAmount: 9
    };
    //----- ����������� -----
    _init(); // ������ ������������� ����� �� ������������ ��� �������, + ����� �� ���������, ����� - initialize().
    //----------

    {//Cell     // ��� � �� ���� �� ��������� ������.
        /**
         * ������� ������� ������
         * @param {number} id
         * ��� HTMLElement
         * @param {number} num
         * ����� ������������ �� ������
         * @param {number} row
         * ����� ���� �� ������� ����. ���������� � 0
         * @param {type} col
         * ����� ������� �� ������� ����. ���������� � 0
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
            cell.style.top = ((row * 100) + "px"); // ���� 100 - ��� ������ ������, �� ����� ������ ���������.
            cell.style.left = ((col * 100) + "px");

            var lbl = document.createElement("div");
            lbl.setAttribute("class", "label");
            lbl.innerHTML = (num === 0) ? "" : num;  // "����������" ����� ����� �� ������������, � ��������� ���������, �-� const EMPTY_HTML = 0.

            cell.appendChild(lbl);

            return cell;
        }

        /**
         * �������� ������ �� ���������� ������ ���� � �������
         * @param {number} row
         * ����� ���� ������. ������ ��� 0
         * @param {number} col
         * ����� ������� ������. ������ �������� 0
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
         * �������� ������ �� ���������� ������ �� �����
         * @param {number} number
         * @returns {Element}
         */
        function getCellByNumber(number) {
            number = parseInt(number);

            var cells = getGame().getElementsByClassName("cell");
            for (var i = 0; i < cells.length; i++) {  // ����� ����������� ����������� ������ ��� �����������, ��� ����� �������� ������� ��������� ����.
                if (parseInt(cells[i].getAttribute("number")) === number) {
                    return cells[i];
                }
            }
        }

        /**
         * ������ ������ ��������� �� �����������. �������� �������� none, up, 
         * down, left, right
         * @param {Element} cell
         * ������
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
         * ���������� ����� ���������� �����
         * @param {Element} cell
         * ������
         * @returns {array}
         * ������ �� ����������
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
         * ������������� ����� � ��������� ���������
         * @param {Element} cell
         * ������
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
     * ���������� ������ ���������� �������� ������ �� 0 �� n
     * @param {number} amount 
     * ������ ���������� ������������ �����
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
        if (element.addEventListener) {  // ��� �������� �� ����������� IE ������ 9
            element.addEventListener(event, callback, false);
        }
        else {
            if (element.attachEvent) {   // IE �� ������ 9
                element.attachEvent("on" + event, callback);
            }
        }
    }

    /**
     * ������������� ����
     */
    function _init() { //initialize
        var el = document.getElementById(elementName);
        if (el) {
            el.setAttribute("class", "field");
        } else {
            throw "[Game] createField: ������� � ������ " + elementName + " �� ������";
        }

        optionsLoad();

        
        var row_count = Math.floor(Math.sqrt(_options.cellAmount));
        _options.cellAmount = row_count*row_count;
        var cells = numberArrayGen(_options.cellAmount);

        //���������� ��������� �� �������� ����
        for (var i = 0; i < cells.length; i++) {
            var row =Math.floor(i / row_count);
            var col =Math.floor(i % row_count);
            var cell = createCell(elementName + "_cell_" + cells[i], cells[i], row, col);
            bindEvent(cell, "click", OnCellClick); // �� ������� ����� ������ ���, ����� ����� ����� cell.onclick = OnCellClick;.
            el.appendChild(cell);
        }

        statusUpdate();
    }

    {//Options
        /**
         * ��������� �������� ����������
         */
        function optionsLoad() {
            if (typeof (options) !== "undefined") {
                optionLoad('cellAmount');
            }
        }

        /**
         * ��������� �������� ����������
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
            //������� ������ ��� ������� ���������� �����
            //�������
            setCellSelectable(getCellByRowCol(row - 1, col));
            setCellMoveAttr(getCellByRowCol(row - 1, col), "down");
            //������
            setCellSelectable(getCellByRowCol((row + 1), col));
            setCellMoveAttr(getCellByRowCol((row + 1), col), "up");
            //������
            setCellSelectable(getCellByRowCol(row, col + 1));
            setCellMoveAttr(getCellByRowCol(row, col + 1), "left");
            //�����
            setCellSelectable(getCellByRowCol(row, col - 1));
            setCellMoveAttr(getCellByRowCol(row, col - 1), "right");
        }

        /**
         * C��� ��������� ��� �����
         */
        function statusReset() {
            var cells = getGame().getElementsByClassName("cell");
            for (var i = 0; i < cells.length; i++) {
                cells[i].setAttribute("class", "cell");
                cells[i].setAttribute("move", "none");
            }
        }

        /**
         * �������� ������������ �����.
         * @returns {Boolean}
         * ���������� ������ ���� ��� ����� ����� �� �������
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
     * ������� ���������� ��� ������� �� ������
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
        switch (direction) { // ������� OnCellClick ��������� 30 �������, ��� ����������� ����� ������� ������� moveCell(cell, direction).
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
 * ������� ��� ������ ��� ���������
 */
function log(msg) {  // ���� ������� ����� �� ������������, � ����� ������.
    var fName = arguments.callee.caller.toString();
    fName = fName.substr('function '.length);
    fName = fName.substr(0, fName.indexOf('('));

    console.log("[" + fName + "] " + msg);
}