
	var wsUri = 'ws://127.0.0.1:9999';
	var input;
	var output; 
	var statusOutput;
	var timeOutput;
	var timeSetErrorOutput;

  	function init()
  	{
    	output = document.getElementById("output");
		timeOutput = document.getElementById("timeOutput");
		statusOutput = document.getElementById("statusOutput");
		input = document.getElementById("input");
		timeSetErrorOutput = document.getElementById("timeSetErrorOutput");
		initWebSocket();
  	}

  	function initWebSocket()
  	{
		websocket = new WebSocket(wsUri, 'my-protocol');
		websocket.onopen = function(evt) { onOpen(evt) };
		websocket.onclose = function(evt) { onClose(evt) };
		websocket.onmessage = function(evt) { onMessage(evt) };
		websocket.onerror = function(evt) { onError(evt) };
  	}

  	function onOpen(evt)
  	{
    	writeStatus("<span style=\"color: green;\">CONNECTED</span>");
  	}

  	function onClose(evt)
  	{
    	writeStatus("<span style=\"color: red;\">DISCONNECTED</span>");
  	}

  	function onMessage(evt)
  	{		
		var time = convertTimeFromMinutes(parseInt(evt.data, 10));	

		if (isNaN(parseInt(time[0], 10)) || isNaN(parseInt(time[1], 10)))
		{
			writeToScreen("Error:" + hours + ":" + minutes);
		}

		writeCurrentTime(time[0], time[1]);
  	}

  	function onError(evt)
  	{
    	writeStatus('<span style="color: red;">ERROR:</span> ' + evt.data);
		websocket.close();
  	}

  	function sendToWebSocket(message)
  	{
    	websocket.send(message);
  	}

 	function writeStatus(message)
  	{
		statusOutput.innerHTML = message;
  	}

	function pad(n, width, z) 
	{
   	z = z || '0';
  		n = n + '';
  		return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
	}

	function setNewTimeTo3DClock()
	{
		clearTimeSetError();

		if (isNaN(inputHours.value) || (parseInt(inputHours.value) < 0 || parseInt(inputHours.value) > 23))
		{
			writeTimeSetError("Invalid hours value");
			return;
		}
		if (isNaN(inputMinutes.value) || (parseInt(inputMinutes.value) < 0 || parseInt(inputMinutes.value) > 59))
		{
			writeTimeSetError("Invalid minutes value");
			return;
		}
		var payload = 1 + pad(parseInt(inputHours.value), 2) + pad(parseInt(inputMinutes.value), 2);

		sendToWebSocket(payload);
  	}

	function requestCurrentTimeFrom3DClock()
	{
		var msg = "x";
		sendToWebSocket(msg);
	}

	// Convert time from minutes past midnight to 24 hour format
	function convertTimeFromMinutes(minutesPastMidnight)
	{
		var minutes = minutesPastMidnight % 60;
		var hours = (minutesPastMidnight-minutes) / 60;
		return [hours, minutes];
	}

	function writeCurrentTime(hours, minutes)
	{
		timeOutput.innerHTML = pad(hours, 2) + ":" + pad(minutes, 2);
	}

	function writeTimeSetError(message)
	{
		timeSetErrorOutput.innerHTML = "<span style=\"color: red;\">" + message + "</span>";
	}

	function clearTimeSetError()
	{
		timeSetErrorOutput.innerHTML = "";
	}

  	window.addEventListener("load", init, false);

