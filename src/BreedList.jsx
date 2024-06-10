import React from 'react';

const BreedList = (props) => {
  const { breeds } = props;

  return (
    <section>
      <h2>Популярные породы</h2>
      <ul>
        {breeds.map((breed, index) => (
          <li key={index}>
            <img src={breed.imageUrl} alt={breed.name} />
            <h3>{breed.name}</h3>
            <p>{breed.description}</p>
          </li>
        ))}
      </ul>
    </section>
  );
};

export default BreedList;