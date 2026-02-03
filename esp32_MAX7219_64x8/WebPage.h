#ifndef WEBPAGE_H
#define WEBPAGE_H

const char WebResponse[] = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nConnection: close\r\n\r\n";

const char WebPage[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>LED Control</title>
<style>
  body { font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; background-color: #f0f2f5; display: flex; justify-content: center; align-items: center; min-height: 100vh; margin: 0; padding: 20px; box-sizing: border-box; }
  .card { background-color: #ffffff; padding: 25px; border-radius: 15px; box-shadow: 0 4px 15px rgba(0,0,0,0.1); width: 100%; max-width: 400px; }
  h2 { text-align: center; color: #333; margin-top: 0; margin-bottom: 20px; font-size: 24px; }
  .form-group { margin-bottom: 15px; }
  label { display: block; margin-bottom: 8px; color: #555; font-weight: 600; font-size: 14px; }
  input[type="text"] { width: 100%; padding: 12px; border: 1px solid #ddd; border-radius: 8px; box-sizing: border-box; font-size: 16px; transition: border-color 0.3s; background-color: #fafafa; }
  input[type="text"]:focus { border-color: #007bff; outline: none; background-color: #fff; }
  .btn-group { display: flex; flex-direction: column; gap: 10px; margin-top: 25px; }
  input[type="button"] { width: 100%; padding: 14px; border: none; border-radius: 8px; font-size: 16px; font-weight: 600; cursor: pointer; transition: background-color 0.2s, transform 0.1s; }
  input[type="button"]:active { transform: scale(0.98); }
  .btn-primary { background-color: #007bff; color: white; }
  .btn-primary:hover { background-color: #0056b3; }
  .btn-secondary { background-color: #6c757d; color: white; }
  .btn-secondary:hover { background-color: #5a6268; }
  #status { text-align: center; margin-top: 15px; color: #28a745; font-weight: 600; min-height: 24px; }
  /* Switch CSS */
  .control-group { display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; padding: 0 5px; }
  .switch { position: relative; display: inline-block; width: 50px; height: 28px; }
  .switch input { opacity: 0; width: 0; height: 0; }
  .slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; transition: .4s; border-radius: 34px; }
  .slider:before { position: absolute; content: ""; height: 20px; width: 20px; left: 4px; bottom: 4px; background-color: white; transition: .4s; border-radius: 50%; }
  input:checked + .slider { background-color: #28a745; }
  input:checked + .slider:before { transform: translateX(22px); }
</style>
<script>
  function sendRequest(url) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", url + "&nocache=" + Math.random(), false);
    xhr.send(null);
  }

  function showStatus(text) {
    var s = document.getElementById("status");
    s.innerText = text;
    setTimeout(function(){ s.innerText = ""; }, 3000);
  }

  function SendText() {
    var m1 = document.getElementById("m1").value;
    var m2 = document.getElementById("m2").value;
    var m3 = document.getElementById("m3").value;
    // 構建與原始程式碼相容的 URL 格式
    var params = "/&MSG1=" + encodeURIComponent(m1) + 
                 "/&MSG2=" + encodeURIComponent(m2) + 
                 "/&MSG3=" + encodeURIComponent(m3) + 
                 "/&TIME=" + Date.now();
    sendRequest(params);
    showStatus("文字已傳送！");
  }

  function ResetText() {
    var params = "/&MSG1=" + encodeURIComponent("Welcome") + 
                 "/&MSG2=" + encodeURIComponent("ESP32 LED") + 
                 "/&MSG3=" + encodeURIComponent("Have a nice day") + 
                 "/&TIME=" + Date.now();
    sendRequest(params);
    showStatus("已重置預設文字！");
    setTimeout(function(){ location.reload(); }, 1000);
  }

  function ResetTime() {
    var params = "/&TIME=" + Date.now();
    sendRequest(params);
    showStatus("時間已校正！");
  }

  function toggleDisplay(cb) {
    sendRequest("/&DISP=" + (cb.checked ? "1" : "0"));
    showStatus(cb.checked ? "顯示已開啟" : "顯示已關閉");
  }

</script>
</head>
<body>
  <div class="card">
    <h2>LED 字幕機控制</h2>
    <form>
      <div class="control-group">
        <label style="margin:0; font-size:16px;">跑馬燈開關</label>
        <label class="switch"><input type="checkbox" onclick="toggleDisplay(this)" __CHECKED__><span class="slider"></span></label>
      </div>
      <div style="text-align: center; color: #666; font-size: 14px; margin-bottom: 20px;">
        自動開關機時間: __WORKTIME__
      </div>
      <div class="form-group">
        <label for="m1">輪播訊息 1</label>
        <input type="text" id="m1" value="__MSG1__" maxlength="100" placeholder="輸入文字..." readonly ontouchstart="this.removeAttribute('readonly');" onclick="this.removeAttribute('readonly');">
      </div>
      <div class="form-group">
        <label for="m2">輪播訊息 2</label>
        <input type="text" id="m2" value="__MSG2__" maxlength="100" placeholder="輸入文字..." readonly ontouchstart="this.removeAttribute('readonly');" onclick="this.removeAttribute('readonly');">
      </div>
      <div class="form-group">
        <label for="m3">輪播訊息 3</label>
        <input type="text" id="m3" value="__MSG3__" maxlength="100" placeholder="輸入文字..." readonly ontouchstart="this.removeAttribute('readonly');" onclick="this.removeAttribute('readonly');">
      </div>
      <div class="btn-group">
        <input type="button" class="btn-primary" value="傳送文字" onclick="SendText()">
        <input type="button" class="btn-secondary" value="重置預設文字" onclick="ResetText()">
        <input type="button" class="btn-secondary" value="校正時間" onclick="ResetTime()">
      </div>
      <div id="status"></div>
    </form>
  </div>
</body>
</html>
)rawliteral";

#endif
