// function shakerSort(arr, compare) {
//     let swapped;
//     do {
//         swapped = false;
//         for (let i = 0; i < arr.length - 1; i++) {
//             if (compare(arr[i], arr[i + 1]) > 0) {
//                 [arr[i], arr[i + 1]] = [arr[i + 1], arr[i]];
//                 swapped = true;
//             }
//         }
//         if (!swapped) break;
//         swapped = false;
//         for (let i = arr.length - 2; i >= 0; i--) {
//             if (compare(arr[i], arr[i + 1]) > 0) {
//                 [arr[i], arr[i + 1]] = [arr[i + 1], arr[i]];
//                 swapped = true;
//             }
//         }
//     } while (swapped);
// }

// function sortTable() {
//     const table = document.getElementById('table');
//     const rows = Array.from(table.querySelectorAll('tr'));
//     rows.shift(); 

//     const selects = document.querySelectorAll('select[name^="sort"]');
//     const selectedOptions = Array.from(selects).map(select => parseInt(select.value));

//     shakerSort(rows, (a, b) => {
//         const sizeOrder = { "Маленький": 0, "Средний": 1, "Большой": 2 };
//         const breedA = a.children[1].textContent;
//         const breedB = b.children[1].textContent;
//         const sizeA = a.children[2].textContent;
//         const sizeB = b.children[2].textContent;
//         const countryA = a.children[4].textContent;
//         const countryB = b.children[4].textContent;

//         if (sizeOrder[sizeA] !== sizeOrder[sizeB]) {
//             return sizeOrder[sizeA] - sizeOrder[sizeB];
//         }
//         if (breedA !== breedB) {
//             return breedA.localeCompare(breedB);
//         }
//         return countryA.localeCompare(countryB);
//     });

//     rows.forEach(row => table.appendChild(row)); 
//     ;
//     selects.forEach(select => {
//         let value = select.value;
//         select.querySelectorAll('option').forEach(option => {
//             let optionValue = option.value;
//             if (optionValue !== value) {
//                 option.disabled = true;
//             } else {
//                 option.disabled = false;
//             }
//         });
//     });
// }
// формирование поля элемента списка с заданным текстом и значением 
let createOption = (str, val) => {
  let item = document.createElement('option');
  item.text = str;
  item.value = val;
  return item;
}
// формирование полей со списком из заголовков таблицы 
// параметры – массив из заголовков таблицы и элемент select 
let setSortSelect = (head, sortSelect) => {
  // создаем OPTION Нет и добавляем ее в SELECT  
  sortSelect.append(createOption('Нет', 0));
  // перебираем все ключи переданного элемента массива данных 
  for (let i in head) {
    // создаем OPTION из очередного ключа и добавляем в SELECT 
    // значение атрибута VAL увеличиваем на 1, так как значение 0 имеет опция Нет  
    // console.log(head);
    // console.log(head[i]);
    sortSelect.append(createOption(head[i], Number(i) + 1));
  }
}
// формируем поля со списком для многоуровневой сортировки 
let setSortSelects = (data, dataForm) => {
  // выделяем ключи словаря в массив  
  let head = Object.keys(data[0]);
  // находим все SELECT в форме  
  let allSelect = dataForm.getElementsByTagName('select');
  for (let j = 0; j < allSelect.length; j++) {
    //формируем опции очередного SELECT  
    setSortSelect(head, allSelect[j]);
    //самостоятельно все SELECT, кроме первого, сделать неизменяемыми  
    if (j > 0) {
      allSelect[j].disabled = true;
    }
  }
}
let originalTable;
// настраиваем поле для следующего уровня сортировки 
let changeNextSelect = (nextSelectId, curSelect) => {
  let nextSelect = document.getElementById(nextSelectId);

  nextSelect.disabled = false;

  // в следующем SELECT выводим те же option, что и в текущем 
  nextSelect.innerHTML = curSelect.innerHTML;

  // удаляем в следующем SELECT уже выбранную в текущем опцию 
  // если это не первая опция - отсутствие сортировки 
  if (curSelect.value != 0) {
    nextSelect.remove(curSelect.value);
  } else {
    nextSelect.disabled = true;
  }
}
let createSortArr = (data) => {
  let sortArr = [];

  let sortSelects = data.getElementsByTagName('select');

  for (let i = 0; i < sortSelects.length; i++) {
    // получаем номер выбранной опции 
    let keySort = sortSelects[i].value;
    // в случае, если выбрана опция Нет, заканчиваем формировать массив 
    if (keySort == 0) {
      break;
    }
    // получаем номер значение флажка для порядка сортировки 
    // имя флажка сформировано как имя поля SELECT и слова Desc 
    let desc = document.getElementById(sortSelects[i].id + 'Desc').checked;
    sortArr.push({ column: keySort - 1, order: desc });
  }
  return sortArr;
};

let sortTable = (idTable, form) => {
  // Формируем массив с настройками сортировки из переданной формы
  let sortArr = createSortArr(form);

  // Если массив с настройками пуст, то возвращаем false, так как сортировка не требуется
  if (sortArr.length === 0) {
    return false;
  }

  // Находим таблицу по ее ID
  let table = document.getElementById(idTable);

  // Преобразуем строки таблицы в массив и удаляем первую строку с заголовками
  let rowData = Array.from(table.rows);
  rowData.shift();

  // Сортируем данные на основе массива с настройками сортировки
  rowData.sort((first, second) => {
    for (let i in sortArr) {
      let key = sortArr[i].column;
      let sortOrder = sortArr[i].order ? -1 : 1; // Если порядок сортировки true, то sortOrder = -1, иначе 1
      if (first.cells[key].innerHTML > second.cells[key].innerHTML) {
        return 1 * sortOrder;
      } else if (first.cells[key].innerHTML < second.cells[key].innerHTML) {
        return -1 * sortOrder;
      }
    }
    return 0; // Если элементы равны, сохраняем текущий порядок
  });

  // Заменяем содержимое таблицы отсортированными данными
  table.innerHTML = table.rows[0].innerHTML;

  // Добавляем отсортированные строки обратно в таблицу
  rowData.forEach(item => {
    table.append(item);
  });
};
// Функция для сброса всех уровней сортировки
let resetAllSorting = () => {
  document.getElementById("fieldsFirstDesc").checked = false;
  document.getElementById("fieldsSecondDesc").checked = false;
  // Находим таблицу по ее ID
  clearTable('list');
  createTable(dogData, 'list');
  // Делаем все поля, кроме первого, неактивными
  let allSelects = dataForm.getElementsByTagName('select');
  for (let i = 1; i < allSelects.length; i++) {
    allSelects[i].disabled = true;
  }
}
document.addEventListener("DOMContentLoaded", function () {
  createTable(dogData, 'list');
  let dataForm = document.getElementById('sort');
  setSortSelects(dogData, dataForm);
});
// обработчик события изменения поля для первого уровня сортировки
document.getElementById('fieldsFirst').addEventListener('change', function () {
  let nextSelectId = 'fieldsSecond';
  let curSelect = this;
  changeNextSelect(nextSelectId, curSelect);
});
function clearTable(idTable) {
  let table = document.getElementById(idTable);
  table.innerHTML = '';
}
// Очищаем содержимое таблицы
let createTable = (data, idTable) => {
  let table = document.getElementById(idTable);

  // Проверяем, есть ли данные в массиве
  if (data.length === 0) {
    let row = document.createElement('tr');
    let td = document.createElement('td');
    td.textContent = 'Нет данных для отображения';
    td.colSpan = '10';
    row.appendChild(td);
    table.appendChild(row);
    return;
  }

  // Создаем заголовочную строку
  let headerRow = document.createElement('tr');
  for (let key in data[0]) {
    let th = document.createElement('th');
    th.textContent = key;
    headerRow.appendChild(th);
    // console.log(headerRow);
  }
  table.appendChild(headerRow);

  // Заполняем строки таблицы
  data.forEach(item => {
    let row = document.createElement('tr');
    for (let key in item) {
      let td = document.createElement('td');
      td.textContent = item[key];
      row.appendChild(td);
      // console.log(row);
    }
    table.appendChild(row);
  });
};
let correspond = {
  "Название породы": "breed",
  "Размер": "size",
  "Рост собаки в среднем": ["heightFrom", "heightTo"],
  "Страна(регион) происхождения": "origin",
  "Средняя продолжительность жизни": ["yearFrom", "yearTo"]
}

let dataFilter = (dataForm) => {
  let dictFilter = {};

  // Перебираем все элементы формы с фильтрами
  for (let j = 0; j < dataForm.elements.length; j++) {
    let item = dataForm.elements[j];
    let valInput = item.value;

    // Приводим значение текстового поля к нижнему регистру
    if (item.type == "text") {
      valInput = valInput.toLowerCase();
    }

    // Обрабатываем значения числовых полей
    if (item.type == "number") {
      // Если поле пустое и его id содержит "From", устанавливаем минимальное значение
      if (valInput === "" && item.id.includes("From")) {
        valInput = -Infinity;
      }
      // Если поле пустое и его id содержит "To", устанавливаем максимальное значение
      else if (valInput === "" && item.id.includes("To")) {
        valInput = Infinity;
      }
      // Преобразуем значение к числу
      else {
        valInput = parseFloat(valInput);
      }
    }

    // Добавляем элемент в ассоциативный массив
    dictFilter[item.id] = valInput;
  }

  return dictFilter;
};

let filterTable = (data, idTable, dataForm) => {
  // Получаем данные из полей формы
  let datafilter = dataFilter(dataForm);

  // Выбираем данные, соответствующие фильтру, и формируем таблицу из них
  let tableFilter = data.filter(item => {
    let result = true;

    // Строка соответствует фильтру, если сравнение всех значений из input со значением ячейки очередной строки - истина
    for (let key in item) {
      let val = item[key];
      // Текстовые поля проверяем на вхождение
      if (typeof val == 'string') {
        val = item[key].toLowerCase()
        result &&= val.indexOf(datafilter[correspond[key]]) !== -1;
      }
      // Числовые поля проверяем на принадлежность интервалу
      else if (typeof val == 'number') {
        if (key === "Рост собаки в среднем") {
          let fromValue = datafilter[`heightFrom`];
          let toValue = datafilter[`heightTo`];
          result &&= val >= fromValue && val <= toValue;
        }
        else {
          let fromValue = datafilter[`yearFrom`];
          let toValue = datafilter[`yearTo`];
          result &&= val >= fromValue && val <= toValue;
        }
      }
    }

    return result;
  });

  // Показываем на странице таблицу с отфильтрованными строками
  clearTable(idTable);
  createTable(tableFilter, idTable);
  //console.log(setSortSelects(Object.keys(dogData[0]), document.getElementById('sort')));
};
function clearFilter() {
  let filterForm = document.getElementById('filterForm');
  let filterInputs = filterForm.getElementsByTagName('input');
  for (let i = 0; i < filterInputs.length; i++) {
    if (filterInputs[i].type === 'text' || filterInputs[i].type === 'number') {
      filterInputs[i].value = '';
    }
  }
  clearTable('list');
  createTable(dogData, 'list')
}
function createArrGraph(data, key) {

  groupObj = d3.group(data, d => d[key]);
  let arrGraph = [];
  for (let entry of groupObj) {
    let minMax = d3.extent(entry[1].map(d => d['Рост собаки в среднем']));
    arrGraph.push({ labelX: entry[0], values: minMax });
  }
  return arrGraph;
}


