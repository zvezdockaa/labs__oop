import React, { useState } from 'react';

const List = (props) => {
  const [firstList, setFirstList] = useState(props.initialList);
  const [secondList, setSecondList] = useState([]);

  const handleItemClick = (item) => {
    const updatedFirstList = [...firstList];
    const updatedSecondList = firstList.filter((listItem) => listItem !== item);
    setFirstList(updatedFirstList);
    setSecondList(updatedSecondList);
  };

  return (
    <div>
      <h2>Список популярных пород</h2>
      <ul>
        {firstList.map((item, index) => (
          <li key={index} onClick={() => handleItemClick(item)}>
            {item}
          </li>
        ))}
      </ul>

      <h2>Выбранные породы</h2>
      <ul>
        {secondList.map((item, index) => (
          <li key={index}>{item}</li>
        ))}
      </ul>
    </div>
  );
};

export default List;