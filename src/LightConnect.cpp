// Copyright (c) 2026 Otto
// Лицензия: MIT (см. LICENSE)

#include "LightConnect.h"

LightConnectCfg lcCfg;
LightConnectClass LightConnect;

static const char LC_PAGE[] PROGMEM = R"raw(<!DOCTYPE html>
<html lang="ru"><head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1">
<title>LightConnect</title>
<style>
*{box-sizing:border-box;margin:0;padding:0}
:root{--bg:#0f1117;--sf:#1a1d27;--cd:#21253a;--br:#2e3350;--ac:#4f8ef7;--a2:#7c5af7;--gn:#22c55e;--rd:#ef4444;--or:#f59e0b;--tx:#e2e8f0;--mt:#64748b;--r:14px}
body{font-family:system-ui,-apple-system,sans-serif;background:var(--bg);color:var(--tx);min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:24px 16px 40px}
.hdr{text-align:center;margin-bottom:24px}
.logo{width:54px;height:54px;border-radius:16px;background:linear-gradient(135deg,var(--ac),var(--a2));display:inline-flex;align-items:center;justify-content:center;margin-bottom:10px;box-shadow:0 4px 20px rgba(79,142,247,.35)}
.logo svg{width:28px;height:28px}
h1{font-size:1.5rem;font-weight:700}
h1 span{background:linear-gradient(90deg,var(--ac),var(--a2));-webkit-background-clip:text;-webkit-text-fill-color:transparent}
.sub{color:var(--mt);font-size:.82rem;margin-top:3px}
.card{background:var(--sf);border:1px solid var(--br);border-radius:var(--r);padding:20px;width:100%;max-width:420px;box-shadow:0 8px 32px rgba(0,0,0,.45);margin-bottom:14px}
.ct{font-size:.72rem;font-weight:600;text-transform:uppercase;letter-spacing:1px;color:var(--mt);margin-bottom:12px;display:flex;align-items:center;gap:7px}
.ct svg{width:15px;height:15px;flex-shrink:0}
.opt{font-size:.68rem;background:rgba(79,142,247,.15);color:var(--ac);border-radius:4px;padding:1px 5px;margin-left:4px}
.f{margin-bottom:10px}
.f label{display:block;font-size:.78rem;color:var(--mt);margin-bottom:5px;font-weight:500}
.iw{position:relative}
.iw .fi{position:absolute;left:11px;top:50%;transform:translateY(-50%);width:17px;height:17px;pointer-events:none;opacity:.5}
input[type=text],input[type=password]{width:100%;background:var(--cd);border:1px solid var(--br);border-radius:10px;padding:10px 38px 10px 38px;color:var(--tx);font-size:.92rem;transition:border-color .2s,box-shadow .2s;outline:none;-webkit-appearance:none}
input:focus{border-color:var(--ac);box-shadow:0 0 0 3px rgba(79,142,247,.18)}
input::placeholder{color:var(--mt)}
.eye{position:absolute;right:10px;top:50%;transform:translateY(-50%);background:none;border:none;cursor:pointer;padding:3px;color:var(--mt);display:flex;align-items:center;transition:color .2s}
.eye:hover{color:var(--tx)}
.eye svg{width:17px;height:17px}
.dvd{height:1px;background:var(--br);margin:14px 0}
.btn{width:100%;border:none;border-radius:10px;padding:12px;font-size:.92rem;font-weight:600;cursor:pointer;transition:transform .1s,opacity .2s;display:flex;align-items:center;justify-content:center;gap:7px;margin-bottom:9px;-webkit-appearance:none}
.btn:active{transform:scale(.97)}
.btn svg{width:17px;height:17px}
.bp{background:linear-gradient(135deg,var(--ac),var(--a2));color:#fff;box-shadow:0 4px 16px rgba(79,142,247,.35)}
.bo{background:rgba(245,158,11,.1);color:var(--or);border:1px solid rgba(245,158,11,.25)}
.br2{background:rgba(239,68,68,.08);color:var(--rd);border:1px solid rgba(239,68,68,.2)}
.sc-btn{width:100%;padding:9px;background:var(--cd);border:1px dashed var(--br);border-radius:10px;color:var(--mt);font-size:.83rem;cursor:pointer;transition:border-color .2s,color .2s;display:flex;align-items:center;justify-content:center;gap:6px}
.sc-btn:hover{border-color:var(--ac);color:var(--ac)}
.sc-btn svg{width:15px;height:15px}
.sc-btn.ld svg{animation:sp .8s linear infinite}
@keyframes sp{to{transform:rotate(360deg)}}
.ov{display:none;position:fixed;inset:0;background:rgba(0,0,0,.7);backdrop-filter:blur(4px);z-index:100;align-items:flex-end;justify-content:center}
.ov.show{display:flex}
.mo{background:var(--sf);border:1px solid var(--br);border-radius:var(--r) var(--r) 0 0;width:100%;max-width:480px;max-height:70vh;display:flex;flex-direction:column;box-shadow:0 -8px 40px rgba(0,0,0,.6)}
.mh{padding:14px 18px;border-bottom:1px solid var(--br);display:flex;align-items:center;justify-content:space-between;flex-shrink:0}
.mh span{font-size:.9rem;font-weight:600}
.mc{padding:10px 10px 20px;overflow-y:auto}
.ni{display:flex;align-items:center;gap:9px;padding:10px;border-radius:10px;cursor:pointer;border:1px solid transparent;transition:background .15s,border-color .15s;margin-bottom:3px}
.ni:hover{background:var(--cd);border-color:var(--br)}
.nn{flex:1;font-size:.88rem;font-weight:500;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
.nr{font-size:.72rem;color:var(--mt);white-space:nowrap}
.sg{display:flex;align-items:flex-end;gap:2px;height:13px;flex-shrink:0}
.sg span{display:block;width:3px;background:var(--mt);border-radius:2px}
.sg span:nth-child(1){height:4px}.sg span:nth-child(2){height:7px}.sg span:nth-child(3){height:10px}.sg span:nth-child(4){height:13px}
.sg.s4 span{background:var(--gn)}
.sg.s3 span:not(:nth-child(4)){background:var(--gn)}
.sg.s2 span:not(:nth-child(3)):not(:nth-child(4)){background:var(--or)}
.sg.s1 span:nth-child(1){background:var(--rd)}
.lk{width:13px;height:13px;opacity:.45;flex-shrink:0}
.se{display:flex;align-items:center;gap:7px;padding:10px 14px;background:var(--cd);border-radius:10px;font-size:.85rem;margin-top:10px}
.se svg{width:16px;height:16px;flex-shrink:0;opacity:.6}
#toast{position:fixed;bottom:22px;left:50%;transform:translateX(-50%) translateY(80px);background:var(--cd);border:1px solid var(--br);border-radius:12px;padding:11px 20px;font-size:.88rem;box-shadow:0 8px 32px rgba(0,0,0,.45);transition:transform .35s cubic-bezier(.34,1.56,.64,1),opacity .3s;opacity:0;pointer-events:none;white-space:nowrap;z-index:999;display:flex;align-items:center;gap:7px}
#toast.show{transform:translateX(-50%) translateY(0);opacity:1}
#toast svg{width:17px;height:17px;flex-shrink:0}
#toast.ok{border-color:rgba(34,197,94,.3)}#toast.ok svg{color:var(--gn)}
#toast.er{border-color:rgba(239,68,68,.3)}#toast.er svg{color:var(--rd)}
.ft{color:var(--mt);font-size:.72rem;margin-top:6px}
</style>
</head><body>

<div class="hdr">
  <div class="logo"><svg viewBox="0 0 24 24" fill="none" stroke="#fff" stroke-width="2" stroke-linecap="round"><path d="M1.5 8.5a13 13 0 0121 0M5 12a10 10 0 0114 0M8.5 15.5a6 6 0 017 0M12 19h.01"/></svg></div>
  <h1><span>Light</span>Connect</h1>
  <p class="sub">Настройка WiFi подключения</p>
</div>

<div class="card">
  <div class="ct">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M5 12.55a11 11 0 0114.08 0M1.42 9a16 16 0 0121.16 0M8.53 16.11a6 6 0 016.95 0M12 20h.01"/></svg>
    WiFi сеть
  </div>
  <div class="f">
    <label>Название сети (SSID)</label>
    <div class="iw">
      <svg class="fi" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M1.5 8.5a13 13 0 0121 0M5 12a10 10 0 0114 0M8.5 15.5a6 6 0 017 0M12 19h.01"/></svg>
      <input type="text" id="ssid" placeholder="Выберите или введите SSID" autocomplete="off" spellcheck="false">
    </div>
  </div>
  <div class="f">
    <label>Пароль WiFi</label>
    <div class="iw">
      <svg class="fi" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2"/><path d="M7 11V7a5 5 0 0110 0v4"/></svg>
      <input type="password" id="pass" placeholder="Пароль WiFi" autocomplete="new-password">
      <button class="eye" type="button" onclick="togglePwd('pass',this)" title="Показать пароль"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg></button>
    </div>
  </div>
  <button class="sc-btn" id="scb" onclick="openScan()">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 12a9 9 0 01-9 9 9 9 0 01-9-9 9 9 0 019-9"/><polyline points="21 3 21 9 15 9"/></svg>
    <span id="sct">Сканировать сети</span>
  </button>
</div>

<div class="card">
  <div class="ct">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M20 21v-2a4 4 0 00-4-4H8a4 4 0 00-4 4v2"/><circle cx="12" cy="7" r="4"/></svg>
    Веб-авторизация<span class="opt">необязательно</span>
  </div>
  <div class="f">
    <label>Логин</label>
    <div class="iw">
      <svg class="fi" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><circle cx="12" cy="8" r="4"/><path d="M4 20c0-4 3.6-7 8-7s8 3 8 7"/></svg>
      <input type="text" id="wl" placeholder="Логин" autocomplete="off" spellcheck="false">
    </div>
  </div>
  <div class="f">
    <label>Пароль</label>
    <div class="iw">
      <svg class="fi" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2"/><path d="M7 11V7a5 5 0 0110 0v4"/></svg>
      <input type="password" id="wp" placeholder="Пароль" autocomplete="new-password">
      <button class="eye" type="button" onclick="togglePwd('wp',this)" title="Показать пароль"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg></button>
    </div>
  </div>
</div>

<div class="card">
  <div class="ct">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><circle cx="12" cy="12" r="3"/><path d="M19.07 4.93A10 10 0 114.93 19.07 10 10 0 0119.07 4.93z"/></svg>
    Управление
  </div>
  <button class="btn bp" onclick="doSave()">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M19 21H5a2 2 0 01-2-2V5a2 2 0 012-2h11l5 5v11a2 2 0 01-2 2z"/><polyline points="17 21 17 13 7 13 7 21"/><polyline points="7 3 7 8 15 8"/></svg>
    Сохранить настройки
  </button>
  <button class="btn bo" onclick="doReboot()">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 12a9 9 0 01-9 9 9 9 0 01-9-9 9 9 0 019-9"/><polyline points="21 3 21 9 15 9"/></svg>
    Перезагрузить ESP
  </button>
  <button class="btn br2" onclick="doExit()">
    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>
    Закрыть портал
  </button>
</div>

<p class="ft">LightConnect v1.0.2</p>

<div class="ov" id="ov" onclick="closeModal(event)">
  <div class="mo">
    <div class="mh">
      <span>Доступные сети</span>
      <button class="eye" style="position:static;transform:none" onclick="closeOv()">
        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>
      </button>
    </div>
    <div class="mc" id="mc"></div>
  </div>
</div>

<div id="toast"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"/></svg><span id="tm"></span></div>

<script>
var tt;

function togglePwd(id,btn){
  var i=document.getElementById(id),show=i.type==='password';
  i.type=show?'text':'password';
  btn.innerHTML=show
    ?'<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M17.94 17.94A10.07 10.07 0 0112 20c-7 0-11-8-11-8a18.45 18.45 0 015.06-5.94M9.9 4.24A9.12 9.12 0 0112 4c7 0 11 8 11 8a18.5 18.5 0 01-2.16 3.19m-6.72-1.07a3 3 0 11-4.24-4.24"/><line x1="1" y1="1" x2="23" y2="23"/></svg>'
    :'<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>';
}

function toast(msg,type){
  var el=document.getElementById('toast');
  el.innerHTML=(type==='ok'
    ?'<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"/></svg>'
    :'<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><circle cx="12" cy="12" r="10"/><line x1="12" y1="8" x2="12" y2="12"/><line x1="12" y1="16" x2="12.01" y2="16"/></svg>'
  )+'<span>'+msg+'</span>';
  el.className='show '+(type==='ok'?'ok':'er');
  clearTimeout(tt);
  tt=setTimeout(function(){el.className=''},3000);
}

function post(url,data,ok,err){
  var x=new XMLHttpRequest(),b=[];
  x.open('POST',url,true);
  x.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
  x.onreadystatechange=function(){if(x.readyState===4){x.status===200?ok&&ok():err&&err()}};
  x.onerror=function(){err&&err()};
  for(var k in data)b.push(encodeURIComponent(k)+'='+encodeURIComponent(data[k]));
  x.send(b.join('&'));
}

function sig(r){var l=r>=-55?4:r>=-67?3:r>=-78?2:1;return'<div class="sg s'+l+'"><span></span><span></span><span></span><span></span></div>'}
function esc(s){return String(s).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;')}

function renderNets(nets){
  var mc=document.getElementById('mc'),h='';
  if(!nets||!nets.length){mc.innerHTML='<p style="text-align:center;color:var(--mt);padding:20px">Сети не найдены</p>';return}
  for(var i=0;i<nets.length;i++){
    var n=nets[i],lk=n.e?'<svg class="lk" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2"/><path d="M7 11V7a5 5 0 0110 0v4"/></svg>':'';
    h+='<div class="ni" onclick="pick(\''+esc(n.s)+'\')">'+sig(n.r)+'<span class="nn">'+esc(n.s)+'</span>'+lk+'<span class="nr">'+n.r+' dBm</span></div>';
  }
  mc.innerHTML=h;
}

function pick(s){
  document.getElementById('ssid').value=s;
  closeOv();
  document.getElementById('pass').focus();
  var se=document.getElementById('se');
  if(!se){se=document.createElement('div');se.id='se';se.className='se';document.getElementById('scb').after(se)}
  se.innerHTML='<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M5 12.55a11 11 0 0114.08 0M1.42 9a16 16 0 0121.16 0M8.53 16.11a6 6 0 016.95 0M12 20h.01"/></svg><span>'+esc(s)+'</span>';
}

// ── Всегда делаем новый запрос к ESP ──────────────────────────────────────
function openScan(){
  var btn=document.getElementById('scb'),lbl=document.getElementById('sct');
  btn.classList.add('ld');
  lbl.textContent='Сканирование...';
  var x=new XMLHttpRequest();
  x.open('GET','/scan',true);
  x.timeout=20000;
  x.onreadystatechange=function(){
    if(x.readyState===4){
      btn.classList.remove('ld');
      lbl.textContent='Обновить список';
      if(x.status===200){
        try{renderNets(JSON.parse(x.responseText));openOv()}
        catch(e){toast('Ошибка ответа','er')}
      }else{toast('Ошибка сканирования','er')}
    }
  };
  x.ontimeout=function(){btn.classList.remove('ld');lbl.textContent='Повторить';toast('Таймаут','er')};
  x.send();
}

function openOv(){document.getElementById('ov').classList.add('show')}
function closeOv(){document.getElementById('ov').classList.remove('show')}
function closeModal(e){if(e.target===document.getElementById('ov'))closeOv()}

function doSave(){
  var s=document.getElementById('ssid').value.trim();
  if(!s){toast('Введите название сети!','er');return}
  post('/save',{ssid:s,pass:document.getElementById('pass').value,webLogin:document.getElementById('wl').value.trim(),webPass:document.getElementById('wp').value},
    function(){toast('Настройки сохранены!','ok')},
    function(){toast('Ошибка сохранения','er')});
}

function doReboot(){
  if(!confirm('Перезагрузить ESP?'))return;
  post('/reboot',{},function(){toast('Перезагрузка...','ok')},function(){toast('Команда отправлена','ok')});
}

function doExit(){
  post('/exit',{},function(){toast('Портал закрыт','ok')},function(){toast('Команда отправлена','ok')});
}
</script>
</body></html>)raw";

// ═════════════════════════════════════════════════════════════════════════════

void LightConnectClass::setAPName(const char* name) {
  strncpy(_apName, name, sizeof(_apName) - 1);
  _apName[sizeof(_apName) - 1] = '\0';
}

void LightConnectClass::setAPPass(const char* pass) {
  strncpy(_apPass, pass, sizeof(_apPass) - 1);
  _apPass[sizeof(_apPass) - 1] = '\0';
}

void LightConnectClass::start() {
  if (_apName[0] == '\0') setAPName(LC_AP_NAME);
  if (_apPass[0] == '\0') setAPPass(LC_AP_PASS);

  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  delay(100);

  IPAddress apIP(LC_AP_IP);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));

  if (strlen(_apPass) >= 8)
    WiFi.softAP(_apName, _apPass, LC_AP_CHANNEL);
  else
    WiFi.softAP(_apName, nullptr, LC_AP_CHANNEL);

  _dns.start(LC_DNS_PORT, "*", apIP);
  _setupRoutes();
  _server.begin();
  _started = true;
  _status  = LC_IDLE;
}

void LightConnectClass::stop() {
  _server.stop();
  _dns.stop();
  WiFi.softAPdisconnect(true);
  _started = false;
}

bool LightConnectClass::tick() {
  if (!_started) return false;
  _dns.processNextRequest();
  _server.handleClient();
#ifdef ESP8266
  yield();
#endif
  if (_status != LC_IDLE) {
    delay(200);
    stop();
    return true;
  }
  return false;
}

void LightConnectClass::run(uint32_t timeout) {
  uint32_t t = millis();
  start();
  while (!tick()) {
    if (millis() - t >= timeout) {
      _status = LC_TIMEOUT;
      stop();
      break;
    }
#ifdef ESP8266
    yield();
#else
    delay(1);
#endif
  }
}

byte LightConnectClass::status()      { return _status; }
void LightConnectClass::resetStatus() { _status = LC_IDLE; }

void LightConnectClass::_setupRoutes() {
  _server.onNotFound([this]() { _sendPage();     });
  _server.on("/",       HTTP_GET,  [this]() { _sendPage();     });
  _server.on("/scan",   HTTP_GET,  [this]() { _handleScan();   });
  _server.on("/save",   HTTP_POST, [this]() { _handleSave();   });
  _server.on("/reboot", HTTP_POST, [this]() { _handleReboot(); });
  _server.on("/exit",   HTTP_POST, [this]() { _handleExit();   });
}

void LightConnectClass::_sendPage() {
  _server.sendHeader("Cache-Control","no-cache,no-store,must-revalidate");
  _server.send_P(200, "text/html", LC_PAGE);
}

void LightConnectClass::_handleSave() {
  if (!_server.hasArg("ssid")) { _server.send(400,"text/plain","Bad Request"); return; }
  strncpy(lcCfg.ssid,     _server.arg("ssid").c_str(),     sizeof(lcCfg.ssid)     - 1); lcCfg.ssid[sizeof(lcCfg.ssid)-1]         = '\0';
  strncpy(lcCfg.pass,     _server.arg("pass").c_str(),     sizeof(lcCfg.pass)     - 1); lcCfg.pass[sizeof(lcCfg.pass)-1]         = '\0';
  strncpy(lcCfg.webLogin, _server.arg("webLogin").c_str(), sizeof(lcCfg.webLogin) - 1); lcCfg.webLogin[sizeof(lcCfg.webLogin)-1] = '\0';
  strncpy(lcCfg.webPass,  _server.arg("webPass").c_str(),  sizeof(lcCfg.webPass)  - 1); lcCfg.webPass[sizeof(lcCfg.webPass)-1]   = '\0';
  _status = LC_SUBMIT;
  _sendOk("saved");
}

void LightConnectClass::_handleScan() {
  int n = WiFi.scanNetworks();
  String j = "[";

  if (n <= 0) {
    WiFi.scanDelete();
    _server.sendHeader("Cache-Control", "no-cache");
    _server.send(200, "application/json", j + "]");
    return;
  }

  // Сортирует индексы сетей RSSI по убыванию
  int* order = new int[n];
  for (int i = 0; i < n; i++) order[i] = i;

  for (int i = 0; i < n - 1; i++) {
    int best = i;
    for (int k = i + 1; k < n; k++) {
      if (WiFi.RSSI(order[k]) > WiFi.RSSI(order[best])) best = k;
    }
    if (best != i) {
      int tmp = order[i];
      order[i] = order[best];
      order[best] = tmp;
    }
  }

  for (int p = 0; p < n; p++) {
    int i = order[p];
    if (p) j += ",";
    String name = WiFi.SSID(i);
    name.replace("\\", "\\\\");
    name.replace("\"", "\\\"");
    j += "{\"s\":\"";
    j += name;
    j += "\",\"r\":";
    j += WiFi.RSSI(i);
    j += ",\"e\":";
#ifdef ESP8266
    j += (WiFi.encryptionType(i) != AUTH_OPEN) ? "true" : "false";
#else
    j += (WiFi.encryptionType(i) != WIFI_AUTH_OPEN) ? "true" : "false";
#endif
    j += "}";
  }

  delete[] order;
  j += "]";
  WiFi.scanDelete();
  _server.sendHeader("Cache-Control", "no-cache");
  _server.send(200, "application/json", j);
}

void LightConnectClass::_handleReboot() { _status = LC_REBOOT; _sendOk("reboot"); }
void LightConnectClass::_handleExit()   { _status = LC_EXIT;   _sendOk("exit");   }

void LightConnectClass::_sendOk(const char* msg) {
  _server.send(200,"application/json",String("{\"s\":\"") + msg + "\"}");
}
