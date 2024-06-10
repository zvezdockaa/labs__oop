import React, { useState, useEffect, useRef } from 'react';
import './DogComponent.css';

const DogComponent = () => {
  const [isDogMoving, setIsDogMoving] = useState(false);
  const [isHappy, setIsHappy] = useState(false);
  const [dogPosition, setDogPosition] = useState({ x: 0, y: 0 });
  const dogRef = useRef(null); //хук для изменения состояния, возвращает изменяемый объект
  const bowlRef = useRef(null);

  const handleKeyDown = (e) => {
    if (!isDogMoving) {
      setIsDogMoving(true);
      setIsHappy(false);
    }
    switch (e.key) {
      case 'ArrowUp':
        setDogPosition(prev => ({ ...prev, y: prev.y - 10 }));
        break;
      case 'ArrowDown':
        setDogPosition(prev => ({ ...prev, y: prev.y + 10 }));
        break;
      case 'ArrowLeft':
        setDogPosition(prev => ({ ...prev, x: prev.x - 10 }));
        break;
      case 'ArrowRight':
        setDogPosition(prev => ({ ...prev, x: prev.x + 10 }));
        break;
      default:
        break;
    }
  };

  const checkCollision = () => { //проверка касания
    if (dogRef.current && bowlRef.current) {
      const dogRect = dogRef.current.getBoundingClientRect();//возвращает размер элемента
      const bowlRect = bowlRef.current.getBoundingClientRect();

      return (
        dogRect.left <= bowlRect.right && //проверка границ
        dogRect.right >= bowlRect.left &&
        dogRect.top <= bowlRect.bottom &&
        dogRect.bottom >= bowlRect.top
      );
    }
    return false;
  };

  useEffect(() => { 
    if (checkCollision()) { //если касается- не двигается и счастлива
      setIsDogMoving(false);
      setIsHappy(true);
    } else {
      setIsHappy(false); //несчастлива
    }
  }, [dogPosition]);

  useEffect(() => {
    window.addEventListener('keydown', handleKeyDown); 
    return () => {
      window.removeEventListener('keydown', handleKeyDown);
    };
  }, []);

  return (
    <div className="scene">
      <div className={`message ${isHappy ? 'visible' : ''}`}>
        Собака счастлива
      </div>
      <img
        src="миска с едой.png"
        className="bowl"
        ref={bowlRef}
      />
      <img
        src="собака бежит.png"
        className={`dog ${isDogMoving ? 'running' : ''}`}
        style={{ transform: `translate(${dogPosition.x}px, ${dogPosition.y}px)` }}
        ref={dogRef}
      />
    </div>
  );
};

export default DogComponent;