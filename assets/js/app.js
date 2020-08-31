// We need to import the CSS so that webpack will load it.
// The MiniCssExtractPlugin is used to separate it out into
// its own CSS file.
import css from "../css/app.css"

// webpack automatically bundles all modules in your
// entry points. Those entry points can be configured
// in "webpack.config.js".
//
// Import dependencies
//
import "phoenix_html"

// Import local files
//
// Local files can be imported directly using relative paths, for example:
import socket from "./socket"

socket.connect()

// Now that you are connected, you can join channels with a topic:
let channel = socket.channel("user:user", {})
channel.join()
  .receive("ok", resp => { console.log("Joined successfully", resp) })
  .receive("error", resp => { console.log("Unable to join", resp) })

var output = window.location.href.split("/").pop();

let elements = document.getElementsByClassName("controller-button");

for(let i = 0; i < elements.length; i++)
  elements[i].addEventListener('click', sendClick, false);

function sendClick(click){
  channel.push('button:press', {id: output, code: parseInt(click.target.id, 16)});
}

let repeatable = document.getElementsByClassName("button-repeatable");

for(let i = 0; i < repeatable.length; i++)
{
  repeatable[i].addEventListener('mousedown', onClick, false);
  repeatable[i].addEventListener('mouseup', onRelease, false);
}

let interval = null;

function onClick(event) {
  interval = setInterval(function() {
    channel.push('button:press', {id: output, code: parseInt(event.target.id, 16)});
  }, 100)
}

function onRelease() {
  clearInterval(interval);
}