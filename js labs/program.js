
function calculate(data) {
  let b1 = Number(data.base1.value);
  let b2 = Number(data.base2.value);
  let b3 = Number(data.base3.value);
  let b4 = Number(data.base4.value);
  let a = Number(data.angle.value);
  let s = Number(data.side.value);
  if (checkInput(b1, b2, b3, b4, s, a)) {
    return false;
  }
  let h_1 = Math.round((Math.sqrt((s ** 2) - (Math.abs(b1 - b2)) ** 2)) * 1000) / 1000;
  let h_2 = Math.round((Math.abs((b3 - b4)) * (Math.tan((a * Math.PI) / 180))) * 1000) / 1000;
  let s_1 = Math.round((((b1 + b2) / 2) * h_1) * 1000) / 1000;
  let s_2 = Math.round(1 / 2 * Math.abs(b3 * b3 - b4 * b4) * (Math.sin(90) * (Math.sin(a)) / Math.sin(Number(90 + a))) * 1000) / 1000;
  let p_1 = Math.round(b1 + b2 + h_1 + s)*1000/1000;
  let p_2 = Math.round(b3 + b4 + h_2 + (h_2 / Math.tan(a)))*1000/1000;
  let output = document.getElementById('output');
  output.innerHTML = "<p>Результат:</p>";
  const dataSelect = document.getElementById('data-select');
  const option = dataSelect.querySelector(`option[value="${dataSelect.value}"]`);
  if (option.value === 'data1') {
    if (data.task1.checked) {
      let newElement1 = document.createElement('p');
      newElement1.innerHTML = "H = " + h_1;
      output.appendChild(newElement1);
    }
    if (data.task2.checked) {
      let newElement2 = document.createElement('p');
      newElement2.innerHTML = "S = " + s_1;
      output.appendChild(newElement2);
    }
    if (data.task3.checked) {
      let newElement3 = document.createElement('p');
      newElement3.innerHTML = "P = " + p_1;
      output.appendChild(newElement3);
    }
  } else if (option.value === 'data2') {
    if (data.task1.checked) {
      let newElement4 = document.createElement('p');
      newElement4.innerHTML = "H = " + h_2;
      output.appendChild(newElement4);
    }
    if (data.task2.checked) {
      let newElement5 = document.createElement('p');
      newElement5.innerHTML = "S = " + s_2;
      output.appendChild(newElement5);
    }
    if (data.task3.checked) {
      let newElement6 = document.createElement('p');
      newElement6.innerHTML = "P = " + p_2;
      output.appendChild(newElement6);
    }
  }
  return true;
}

function showInput() {
  const dataSelect = document.getElementById('data-select');
  const option = dataSelect.querySelector(`option[value="${dataSelect.value}"]`);
  if (option.value === 'data1') {
    document.getElementById('input1').style.display = 'block';
    document.getElementById('input2').style.display = 'none';
  } else if (option.value === 'data2') {
    document.getElementById('input1').style.display = 'none';
    document.getElementById('input2').style.display = 'block';
  }
}

function clearInput() {
  let inputs = document.getElementsByTagName('input');
  for (let i = 0; i < inputs.length; i++) {
    if (inputs[i].type === 'text') {
      inputs[i].value = '';
      inputs[i].style.borderColor = '';
    }
  }
  document.getElementById('task1').checked = false;
  document.getElementById('task2').checked = false;
  document.getElementById('task3').checked = false;
  let output = document.getElementById('output');
  output.innerHTML = '';
  const dataSelect = document.getElementById('data-select');
  const option = dataSelect.querySelector(`option[value="${dataSelect.value}"]`);

  document.getElementById('input1').style.display = 'none';
  document.getElementById('input2').style.display = 'none';

  if (option.value === 'data1') {
    document.getElementById('input1').style.display = 'block';
  } else if (option.value === 'data2') {
    document.getElementById('input2').style.display = 'block';
  }
}

function checkInput(b1, b2, b3, b4, s, a) {
  let invalidInput = false;
  const dataSelect = document.getElementById('data-select');
  const option = dataSelect.querySelector(`option[value="${dataSelect.value}"]`);
  if (option.value === 'data1') {
    if (!validateInput('base1', b1)) invalidInput = true;
    if (!validateInput('base2', b2)) invalidInput = true;
    if (!validateInput('side', s)) invalidInput = true;
  }
  if (option.value === 'data2') {
    if (!validateInput('base3', b3)) invalidInput = true;
    if (!validateInput('base4', b4)) invalidInput = true;
    if (!validateInput('angle', a)) invalidInput = true;
  }

  return invalidInput;
}

function validateInput(inputId, value) {
  let inputField = document.getElementById(inputId);
  if (isNaN(parseFloat(value)) || !isFinite(value) || value <= 0) {
    inputField.style.borderColor = 'red';
    return false;
  } else {
    inputField.style.borderColor = '';
    return true;
  }
}