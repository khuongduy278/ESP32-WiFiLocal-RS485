const char htmlContent[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Data validation interface</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style>
      body {
        font-family: Arial, sans-serif;
      }
      .container {
        width: 95%;
        max-width: 450px;
        margin: 0 auto;
        padding: 20px;
        border: 1px solid #ccc;
        border-radius: 5px;
        background-color: #f5f5f5;
        overflow: auto;
        display: flex;
        flex-direction: column;
        align-items: stretch;
      }
      .header {
        text-align: center;
      }
      .frame {
        flex: 1;
        margin-bottom: 20px;
        display: flex;
        flex-direction: column;
      }
      .table {
        width: 100%;
        border-collapse: collapse;
      }
      .table th,
      .table td {
        padding: 10px;
        text-align: left;
        border: 1px solid #ccc;
        background-color: #fff;
      }
      .table th {
        text-align: center;
      }

      .table .header-row th {
        background-color: skyblue;
      }
      .button {
        text-align: center;
      }
      .button button {
        padding: 10px 20px;
        font-size: 16px;
        background-color: #4caf50;
        color: #fff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      .button button:hover {
        background-color: #45a049;
      }

      .right-column {
        text-align: center;
        flex: 1;
      }
      .left-column {
        text-align: center;
      }
      .right-column input[type="text"] {
        width: 100%;
        box-sizing: border-box;
      }
      .right-column select {
        width: 100%;
        padding: 8px;
        border: 1px solid #ccc;
        border-radius: 5px;
        box-sizing: border-box;
      }
      .column-container {
        display: flex;
        flex-wrap: wrap;
      }
      .column-container .column {
        flex: 1;
      }
      .hidden {
        display: none;
      }
      .data-send-container {
        display: flex;
        flex-direction: column;
        align-items: center;
        text-align: center;
      }
      .data-send-container input[type="text"] {
        max-width: 100px;
        box-sizing: border-box;
      }
      .hidden-row {
        display: none;
      }
      .button-container {
        display: flex;
        align-items: center;
        justify-content: space-between;
      }
      .button-container button {
        font-size: 18px;
        background-color: #4caf50;
        color: #fff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
        padding: 5px 10px;
      }
      .button-container button:hover {
        background-color: #45a049;
      }
      .centered {
        margin: 0 auto;
      }
      #rs485Options {
        margin: 0 auto;
        display: block;
      }
      .analog-inputs {
        display: none;
      }

      .show-analog-inputs .analog-inputs {
        display: table-cell;
      }
      .input-half-width {
        width: calc(50% - 1px); 
        margin: 0;
      }
      .digital-inputs,
      .customize-inputs {
        display: none;
      }
      .show-digital-inputs .digital-inputs,
      .show-customize-inputs .customize-inputs {
        display: table-cell;
      }
      .input-small {
        width: 40px; 
      }
    </style>
    <script>
      function toggleMode() {
        var modeSelect = document.getElementById("modeSelect");
        var otaaSettings = document.querySelectorAll(".hidden#otaaSettings");
        var abpSettings = document.querySelectorAll(".hidden#abpSettings");

        if (modeSelect.value === "OTAA") {
          otaaSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (modeSelect.value === "ABP") {
          otaaSettings.forEach((element) => {
            element.style.display = "none";
          });
          abpSettings.forEach((element) => {
            element.style.display = "table-row";
          });
        } else {
          otaaSettings.forEach((element) => {
            element.style.display = "none";
          });
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleClass() {
        var classSelect = document.getElementById("classSelect");
        var abpSettings = document.querySelectorAll(".hidden#abpSettings");
        var classSettings = document.querySelectorAll(".hidden#otaaSettings");

        if (classSelect.value === "A" || classSelect.value === "C") {
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
          classSettings.forEach((element) => {
            element.style.display = "table-row";
          });
        } else {
          abpSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          classSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }
      function checkmodeSelect() {
        var modeSelect = document.getElementById("modeSelect").value;

        if (modeSelect === "OTAA") {
          document
            .getElementById("modeSelect")
            .setAttribute("data-type", "OTAA");
        } else {
          document
            .getElementById("modeSelect")
            .setAttribute("data-type", "ABP");
        }
      }

      function checkclassSelect() {
        var classSelect = document.getElementById("classSelect").value;

        if (classSelect === "A") {
          document.getElementById("classSelect").setAttribute("data-type", "A");
        } else {
          document.getElementById("classSelect").setAttribute("data-type", "C");
        }
      }

      function toggleRS485Settings() {
        var rs485Options = document.getElementById("rs485Options").value;
        var tempHumSettings = document.querySelectorAll(".tempHumSettings");
        var phSettings = document.querySelectorAll(".phSettings");
        var customSettings = document.querySelectorAll(".customSettings");

        if (rs485Options === "Temp/Hum") {
          tempHumSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "PH") {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "custom") {
          customSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleRS485Data() {
        var rs485Options = document.getElementById("rs485Options").value;
        var tempHumSettings = document.querySelectorAll(".tempHumSettings");
        var phSettings = document.querySelectorAll(".phSettings");
        var customSettings = document.querySelectorAll(".customSettings");

        if (rs485Options === "Temp/Hum") {
          tempHumSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "PH") {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "custom") {
          customSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleDataType(selectElement) {
        var dataRow = selectElement.closest(".data-row");
        var dataInputs = dataRow.querySelectorAll(".data-inputs");
        var dataType = selectElement.value;

        dataInputs.forEach(function (input) {
          input.style.display = "none";
        });

        if (dataType === "Analog") {
          var analogInputs = dataRow.querySelectorAll(".analog-inputs");
          analogInputs.forEach(function (input) {
            input.style.display = "table-cell";
          });
        } else if (dataType === "Digital" || dataType === "Customize") {
          var digitalInputs = dataRow.querySelectorAll(".digital-inputs");
          digitalInputs.forEach(function (input) {
            input.style.display = "table-cell";
          });
        }

        // Concatenate values if the selected type is Analog
        if (dataType === "Analog") {
          dataRow.querySelector(".digital-inputs #value13").value =
            dataRow.querySelector(".analog-inputs #value30").value +
            "," +
            dataRow.querySelector(".analog-inputs #value31").value;

          dataRow.querySelector(".digital-inputs #value15").value =
            dataRow.querySelector(".analog-inputs #value32").value +
            "," +
            dataRow.querySelector(".analog-inputs #value33").value;

          dataRow.querySelector(".digital-inputs #value17").value =
            dataRow.querySelector(".analog-inputs #value34").value +
            "," +
            dataRow.querySelector(".analog-inputs #value35").value;

          dataRow.querySelector(".digital-inputs #value19").value =
            dataRow.querySelector(".analog-inputs #value36").value +
            "," +
            dataRow.querySelector(".analog-inputs #value37").value;

          dataRow.querySelector(".digital-inputs #value21").value =
            dataRow.querySelector(".analog-inputs #value38").value +
            "," +
            dataRow.querySelector(".analog-inputs #value39").value;
        }
      }

      function toggleDataRows() {
        var dataRows = document.querySelectorAll(".data-row");

        if (dataRowCount < 5) {
          dataRowCount++;
          dataRows[dataRowCount - 1].style.display = "table-row";
        }

        var addButton = document.querySelector(".add-button");
        var removeButton = document.querySelector(".remove-button");

        addButton.disabled = dataRowCount >= 5;
        removeButton.disabled = dataRowCount <= 0;
      }

      function addDataRow(button) {
        var hiddenRow = document.querySelector(".hidden-row");
        if (hiddenRow) {
          hiddenRow.classList.remove("hidden-row");
          dataRowCount++;
        }

        var addButton = document.querySelector(".add-button");
        addButton.disabled = dataRowCount >= 5;

        var removeButton = document.querySelector(".remove-button");
        removeButton.disabled = dataRowCount <= 0;
      }

      function removeDataRow(button) {
        var row = button.parentNode.parentNode;
        row.style.display = "none";
        dataRowCount--;

        var addButton = document.querySelector(".add-button");
        addButton.disabled = dataRowCount >= 5;

        var removeButton = document.querySelector(".remove-button");
        removeButton.disabled = dataRowCount <= 0;
      }

      document.addEventListener("DOMContentLoaded", function () {
        var addButton = document.querySelector(".add-button");
        var removeButton = document.querySelector(".remove-button");

        // Initialize dataRowCount based on the initial number of visible data rows
        dataRowCount = document.querySelectorAll(
          ".data-row:not(.hidden-row)"
        ).length;

        addButton.disabled = dataRowCount >= 5;
        removeButton.disabled = dataRowCount <= 0;

        var addDataButtons = document.querySelectorAll(".add-data-button");
        addDataButtons.forEach(function (button) {
          button.addEventListener("click", function () {
            addDataRow(button);
          });
        });
      });

      function sendValues() {
        var dataType;
        var value1 = document.getElementById("value1").value;
        var value2 = document.getElementById("value2").value;
        var value3 = document.getElementById("value3").value;
        var value4 = document.getElementById("value4").value;
        var value5 = document.getElementById("value5").value;
        var value6 = document.getElementById("value6").value;
        var value7 = document.getElementById("value7").value;
        var value8 = document.getElementById("value8").value;
        var value9 = document.getElementById("value9").value;
        var value10 = document.getElementById("value10").value;
        var value11 = document.getElementById("value11").value;
        var value12 = document.getElementById("value12").value;
        var value14 = document.getElementById("value14").value;
        var value16 = document.getElementById("value16").value;
        var value18 = document.getElementById("value18").value;
        var value20 = document.getElementById("value20").value;

        var dataType1 = document.getElementById("dataType1").value;
        var dataType2 = document.getElementById("dataType2").value;
        var dataType3 = document.getElementById("dataType3").value;
        var dataType4 = document.getElementById("dataType4").value;
        var dataType5 = document.getElementById("dataType5").value;

        if (dataType1 === "Analog") {
          var value30 = document.getElementById("value30").value;
          var value31 = document.getElementById("value31").value;
          var value13 = [value30, value31];
        }else {
          var value13 = document.getElementById("value13").value;
        }
        if (dataType2 === "Analog" ){
          var value32 = document.getElementById("value32").value;
          var value33 = document.getElementById("value33").value;
          var value15 = [value32, value33];
        }else {
          var value15 = document.getElementById("value15").value;
        }
        if (dataType3 === "Analog"){
          var value34 = document.getElementById("value34").value;
          var value35 = document.getElementById("value35").value;
          var value17 = [value34, value35];
        }else {
          var value17 = document.getElementById("value17").value;
        }
        if (dataType4 === "Analog"){
          var value36 = document.getElementById("value36").value;
          var value37 = document.getElementById("value37").value;
          var value19 = [value36, value37];
        }else {
          var value19 = document.getElementById("value19").value;
        }
        if (dataType5 === "Analog"){
          var value38 = document.getElementById("value38").value;
          var value39 = document.getElementById("value39").value;
          var value21 = [value38, value39];
      }else {
          var value21 = document.getElementById("value21").value;
        }

        var tempInput = document.getElementById("tempInput").value;
        var humInput = document.getElementById("humInput").value;
        var customInput1 = document.getElementById("customInput1").value;
        var ByteSelect1 = document.getElementById("ByteSelect1").value;
        var ByteSelect2 = document.getElementById("ByteSelect2").value;
        var customInput2 = [ByteSelect1, ByteSelect2];
        var customInput3 = document.getElementById("customInput3").value;
        var ByteSelect3 = document.getElementById("ByteSelect3").value;
        var ByteSelect4 = document.getElementById("ByteSelect4").value;
        var customInput4 = [ByteSelect3, ByteSelect4];

        var modeSelect = document.getElementById("modeSelect").value;
        var classSelect = document.getElementById("classSelect").value;
        var rs485Options = document.getElementById("rs485Options").value;
        
        var xhr = new XMLHttpRequest();
        xhr.open("POST", "/process", true);
        xhr.setRequestHeader(
          "Content-Type",
          "application/x-www-form-urlencoded"
        );
        xhr.onreadystatechange = function () {
          if (xhr.readyState === 4 && xhr.status === 200) {
            var successMessage = document.createElement("div");
            successMessage.className = "success-message";
            successMessage.style.cssText = "width: 300px; height: auto; padding: 20px; border: 1px solid #ccc; border-radius: 10px; background-color: #3498db; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.3); position: fixed; top: 50%; left: 50%; transform: translate(-50%, -50%); display: flex; flex-direction: column; align-items: center; justify-content: center;";
            
            var successText = document.createElement("div");
            successText.innerHTML = "Send success";
            successText.style.cssText = "color: #fff; margin-bottom: 20px; text-align: center; font-weight: bold; font-size: 24px;";
            
            var okButton = document.createElement("button");
            okButton.innerHTML = "OK";
            okButton.style.cssText = "background-color: #2ecc71; border: none; border-radius: 5px; padding: 10px 20px; color: #fff; cursor: pointer; font-size: 18px;";
            okButton.onclick = function () {
              countdown();
              successMessage.style.display = "none";
            };
            
            successMessage.appendChild(successText);
            successMessage.appendChild(okButton);
            document.body.appendChild(successMessage);}
        };
        xhr.send(
          "value1=" + encodeURIComponent(value1) +
            "&value2=" + encodeURIComponent(value2) +
            "&value3=" + encodeURIComponent(value3) +
            "&value4=" + encodeURIComponent(value4) +
            "&value5=" + encodeURIComponent(value5) +
            "&value6=" + encodeURIComponent(value6) +
            "&value7=" + encodeURIComponent(value7) +
            "&value8=" + encodeURIComponent(value8) +
            "&value9=" + encodeURIComponent(value9) +
            "&value10=" + encodeURIComponent(value10) +
            "&value11=" + encodeURIComponent(value11) +
            "&value12=" + encodeURIComponent(value12) +
            "&value13=" + encodeURIComponent(value13) +
            "&value14=" + encodeURIComponent(value14) +
            "&value17=" + encodeURIComponent(value17) +
            "&value15=" + encodeURIComponent(value15) +
            "&value16=" + encodeURIComponent(value16) +
            "&value18=" + encodeURIComponent(value18) +
            "&value19=" + encodeURIComponent(value19) +
            "&value20=" + encodeURIComponent(value20) +
            "&tempInput=" + encodeURIComponent(tempInput) +
            "&humInput=" + encodeURIComponent(humInput) +
            "&customInput1=" + encodeURIComponent(customInput1) +
            "&customInput2=" + encodeURIComponent(customInput2) +
            "&customInput3=" + encodeURIComponent(customInput3) +
            "&customInput4=" + encodeURIComponent(customInput4) +
            "&value21=" + encodeURIComponent(value21) +
            "&modeSelect=" + encodeURIComponent(modeSelect) +
            "&classSelect=" + encodeURIComponent(classSelect) +
            "&rs485Options=" + encodeURIComponent(rs485Options) +
            "&dataType1=" + encodeURIComponent(dataType1) +
            "&dataType2=" + encodeURIComponent(dataType2) +
            "&dataType3=" + encodeURIComponent(dataType3) +
            "&dataType4=" + encodeURIComponent(dataType4) +
            "&dataType5=" + encodeURIComponent(dataType5)
        );
      }

      function countdown() {
        var count = 5;
        var countdownMessage = document.createElement("div");
        countdownMessage.style.cssText = "position:fixed;top:50%;left:50%;transform:translate(-50%,-50%);fontSize:18px;";
        countdownMessage.innerHTML = "Page will close in " + count + "s...";
      
        document.querySelector(".container").appendChild(countdownMessage);
      
        var countdownInterval = setInterval(function () {
          if (--count <= 0) {
            clearInterval(countdownInterval);
            window.location.href = "/thankyou.html";
          } else {
            countdownMessage.innerHTML = "Page will close in " + count + "s...";
          }
        }, 1000);
      }
    </script>
  </head>
  <body>
    <div class="container">
      <div class="frame">
        <div class="header">
          <h2 style="text-align: center">TMA Innovation</h2>
        </div>
        <div class="column-container">
          <!-- Cột LoRaWAN -->
          <div class="column" id="lorawanTable">
            <table class="table">
              <tr class="header-row">
                <th colspan="2">LoRaWAN</th>
              </tr>
              <tr>
                <th>Mode</th>
                <td>
                  <select id="modeSelect" onchange="toggleMode()">
                    <option value="">-- Select Mode --</option>
                    <option value="ABP">ABP</option>
                    <option value="OTAA">OTAA</option>
                  </select>
                </td>
              </tr>
              <!-- Ẩn bảng thông số chế độ OTAA ban đầu -->
              <tr class="hidden" id="otaaSettings">
                <th>Class</th>
                <td>
                  <select id="classSelect" onchange="toggleClass()">
                    <option value="">-- Select Class --</option>
                    <option value="A">A</option>
                    <option value="C">C</option>
                  </select>
                </td>
              </tr>
              <tr class="hidden" id="otaaSettings">
                <th>Dev_EUI</th>
                <td><input id="value1" type="text" /></td>
              </tr>
              <tr class="hidden" id="otaaSettings">
                <th>APP_EUI</th>
                <td><input id="value2" type="text" /></td>
              </tr>
              <tr class="hidden" id="otaaSettings">
                <th>APP KEY</th>
                <td><input id="value3" type="text" /></td>
              </tr>
              <tr class="hidden" id="otaaSettings">
                <th>Interval</th>
                <td><input id="value4" type="text" /></td>
              </tr>
              <!-- Hiển thị bảng thông số chế độ ABP ban đầu -->
              <tr class="hidden" id="abpSettings">
                <th>Class</th>
                <td>
                  <select id="classSelect" onchange="toggleClass()">
                    <option value="">-- Select Class --</option>
                    <option value="A">A</option>
                    <option value="C">C</option>
                  </select>
                </td>
              </tr>
              <tr class="hidden" id="abpSettings">
                <th>Dev_addr</th>
                <td><input id="value5" type="text" /></td>
              </tr>
              <tr class="hidden" id="abpSettings">
                <th>NWK</th>
                <td><input id="value6" type="text" /></td>
              </tr>
              <tr class="hidden" id="abpSettings">
                <th>APPs KEY</th>
                <td><input id="value7" type="text" /></td>
              </tr>
              <tr class="hidden" id="abpSettings">
                <th>Interval</th>
                <td><input id="value8" type="text" /></td>
              </tr>
            </table>
          </div>
        </div>
      </div>

      <!--  RS485 -->
      <div class="frame">
        <div class="column-container">
          <div class="column" id="rs485Table">
            <table class="table">
              <tr class="header-row">
                <th colspan="3">RS485 Options:</th>
              </tr>
              <tr>
                <td colspan="3" class="centered">
                  <select id="rs485Options" onchange="toggleRS485Settings()">
                    <option value="">-- Select --</option>
                    <option value="Temp/Hum">Temp/Hum</option>
                    <option value="PH">PH</option>
                    <option value="custom">Customize</option>
                  </select>
                </td>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td>BaudRates</td>
                <td>RS485</td>
                <td>4800</td>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td>ByteSend</td>
                <td>RS485</td>
                <td>010300000002</td>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td>RS485 Configure</td>
                <td>RS485</td>
                <td>8N1</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td>BaudRates</td>
                <td>RS485</td>
                <td>4800</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td>ByteSend</td>
                <td>RS485</td>
                <td>010300000002</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td>RS485 Configure</td>
                <td>RS485</td>
                <td>8N1</td>
              </tr>
              <tr class="hidden-row customSettings">
                <td>BaudRates</td>
                <td><input id="value9" type="text" /></td>
              </tr>
              <tr class="hidden-row customSettings">
                <td>ByteSend</td>
                <td><input id="value10" type="text" /></td>
              </tr>
              <tr class="hidden-row customSettings">
                <td>RS485 Configure</td>
                <td><input id="value11" type="text" /></td>
              </tr>
            </table>
          </div>
        </div>
      </div>

      <!-- Data Send RS485 -->
      <div class="frame">
        <div class="column-container">
          <div class="column" id="rs485Table">
            <table class="table">
              <tr class="header-row">
                <th colspan="3">Send Data RS485:</th>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td><input id="tempInput" type="text" /></td>
                <td>RS485</td>
                <td>[3][4]</td>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td><input id="humInput" type="text" /></td>
                <td>RS485</td>
                <td>[5][6]</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td><input id="tempInput1" type="text" /></td>
                <td>RS485</td>
                <td>[3][4]</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td><input id="humInput1" type="text" /></td>
                <td>RS485</td>
                <td>[5][6]</td>
              </tr>
              <tr class="hidden-row customSettings">
                <td><input id="customInput1" type="text" /></td>
                <td>
                  <select id="ByteSelect1" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                  <select id="ByteSelect2" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                </td>
              </tr>
              <tr class="hidden-row customSettings">
                <td><input id="customInput3" type="text" /></td>
                <td>
                  <select id="ByteSelect3" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                  <select id="ByteSelect4" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                </td>
              </tr>
            </table>
          </div>
        </div>
      </div>
      <!-- DataSend -->
      <div class="frame">
        <div class="column-container">
          <div class="column" id="dataSendTable">
            <div class="data-send-container">
              <table class="table">
                <tr class="header-row">
                  <th colspan="4">DataSend</th>
                </tr>
                <tr class="hidden-row data-row" id="dataRow1">
                  <td><input type="text" id="value12" /></td>
                  <td>
                    <select id="dataType1" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value30" class="input-small" /> -
                    <input type="text" id="value31" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value13" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow2">
                  <td><input type="text" id="value14" /></td>
                  <td>
                    <select id="dataType2" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value32" class="input-small" /> -
                    <input type="text" id="value33" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value15" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow3">
                  <td><input type="text" id="value16" /></td>
                  <td>
                    <select id="dataType3" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value34" class="input-small" /> -
                    <input type="text" id="value35" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value17" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow4">
                  <td><input type="text" id="value18" /></td>
                  <td>
                    <select id="dataType4" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value36" class="input-small" /> -
                    <input type="text" id="value37" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value19" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow5">
                  <td><input type="text" id="value20" /></td>
                  <td>
                    <select id="dataType5" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value38" class="input-small" /> -
                    <input type="text" id="value39" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value21" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
              </table>
            </div>
          </div>
        </div>
      </div>

      <div class="button">
        <button type="button" onclick="toggleDataRows()">+</button>
        <button type="button" onclick="sendValues()">Send</button>
      </div>
      <div class="button">
        <form id="uploadForm" method="POST" enctype="multipart/form-data" style="display: inline">
          <input type="file" name="update" />
          <button type="button" onclick="updateFirmware()">updateOTA</button>
        </form>
      </div>
      <div id="firmwareStatus"></div>
      </div>
    </div>
  </body>
</html>
)=====";
