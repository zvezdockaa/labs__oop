import React, { useState } from 'react';
import './index.css';

const LandingPage = () => { 
  const [showMoreInfo, setShowMoreInfo] = useState(false);

  const handleShowMore = () => { //показ информации
    setShowMoreInfo(true);
  };

  const handleHide = () => { //скрыть текст
    setShowMoreInfo(false);
  };

  return (
    <div className='Landing'>
      <header>
        <nav>
          <ul>
            <li><a href="#">Главная</a></li>
            <li><a href="#">Породы</a></li>
            <li><a href="#">О нас</a></li>
            <li><a href="#">Контакты</a></li>
          </ul>
        </nav>
      </header>

      <main>
        <section>
          <h1>Добро пожаловать на сайт о породах собак</h1>
          <p>Здесь вы найдете исчерпывающую информацию о различных породах собак, их характеристиках и особенностях содержания.</p>
          <button onClick={handleShowMore}>Узнать больше</button>
        {/* если нажата кнопка, то показывается информация */}
          {showMoreInfo && (
            <div className="more-info">
              <p>Мы очень любим собак и хотим поделиться этой любовью с вами. Узнайте о темпераменте, уходе, тренировках и многом другом для каждой породы. Независимо от того, ищете ли вы нового члена семьи или просто увлекаетесь собаками, мы здесь, чтобы помочь!</p>
              <button onClick={handleHide}>Скрыть</button>
            </div>
          )}
        </section>
      </main>
    </div>
  );
};

export default LandingPage;