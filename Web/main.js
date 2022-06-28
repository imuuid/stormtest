document.getElementById("mainContainer").innerHTML = "<div class='loader-wrapper hidden'> <img class='loader' src='guiLogo.png'></div><div> <div class='container d-flex justify-content-center'> <div id='guiMain' class='guiBox shadow'> <div id='guiMainTitle' class='titleBar'> <span> <p class='spacer circle red' onclick='closeGui()'></p><p class='spacer circle yellow'></p><p class='spacer circle green'></p></span> </div><img class='guiLogo' src='http://localhost/cheat/guiLogo.png'> <div class='cpsControl'> <p id='cpsValue'>CPS: 14</p><input type='range' id='cps_range' name='cpsSet' min='1' max='25' value='14'step='1' oninput='updateRange(this.value)'> </div><div class='keyBindControl'> <p class='spacer'>KEYBIND</p><button id='buttonKey' class='spacer buttonGui' onclick='waitingKeypress()'>R</button> </div><div class='bottomGui'> <button class='buttonGui' onclick='closeGui()'>Close</button> <a href='https://t.me/stehack' target='_blank'><i class='float-end spacer fa-brands fa-telegram'></i></a> <a href='https://github.com/stehack27/storm' target='_blank'><i class='float-end spacer fab fa-github'></i></a> </div></div></div></div>";

var setKey = 82
function waitingKeypress() {
  var button = document.getElementById("buttonKey")
  button.innerHTML = "Press KEY"
  return new Promise((resolve) => {
    document.addEventListener('keydown', onKeyHandler);
    function onKeyHandler(e) {
      setKey = e.keyCode
      button.innerHTML = e.key.toUpperCase()
      updateValue()
    }
  });
}

dragElement(document.getElementById("guiMain"));
function dragElement(elmnt) {
  var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
  if (document.getElementById(elmnt.id + "Title")) {
    /* if present, the header is where you move the DIV from:*/
    document.getElementById(elmnt.id + "Title").onmousedown = dragMouseDown;
  } else {
    /* otherwise, move the DIV from anywhere inside the DIV:*/
    elmnt.onmousedown = dragMouseDown;
  }

  function dragMouseDown(e) {
    e = e || window.event;
    e.preventDefault();
    // get the mouse cursor position at startup:
    pos3 = e.clientX;
    pos4 = e.clientY;
    document.onmouseup = closeDragElement;
    // call a function whenever the cursor moves:
    document.onmousemove = elementDrag;
  }

  function elementDrag(e) {
    e = e || window.event;
    e.preventDefault();
    // calculate the new cursor position:
    pos1 = pos3 - e.clientX;
    pos2 = pos4 - e.clientY;
    pos3 = e.clientX;
    pos4 = e.clientY;
    // set the element's new position:
    elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
    elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
  }

  function closeDragElement() {
    /* stop moving when mouse button is released:*/
    document.onmouseup = null;
    document.onmousemove = null;
  }
}


function updateRange(value){
    document.getElementById("cpsValue").innerHTML = "CPS: " + value;
}

rangeInput = document.querySelector('input');
rangeInput.addEventListener('change', function(){
  updateValue()
});

function updateValue(){
  $.ajax({
    type: "POST",
    data:{name: rangeInput.value, surname: setKey}
})
}

function closeGui(){
    $.ajax({
        type: "POST", 
        data:{nick: "close"}
    })
    $(".guiBox:first-child").addClass('guiFade');
    $('.guiBox').on('transitionend', function(e){
      $(e.target).remove()
  });
};
