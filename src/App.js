
import React from 'react';
import LandingPage from './LandingPage';
import BreedList from './BreedList';
import Footer from './Footer';
import DogComponent from './DogComponent';
import List from './List';

const breeds = [
  {
    imageUrl: 'керн-терьер.jpg',
    name: 'Керн-терьер',
    description: 'Керн-терьер, или кэрнтерьер — одна из самых старых пород среди терьеров. Порода известна как одна из самых ранних рабочих собак Шотландии. Керн-терьеров вывели на западе северной высокогорной части Шотландии для охоты в кернах — грудах камней — на кроликов и лисиц.'
  },
  {
    imageUrl: 'мастиф.jpg',
    name: 'Мастиф',
    description: 'Родиной испанского мастифа является Испания — Эстремадура. Происходит от смешения боевых, пастушьих и сторожевых собак древних кельтов и пиренейских горных собак. Изначально данная порода была выведена как фермерская, она предназначалась для охраны сельскохозяйственных угодий и использовалась весьма активно.'},
  {
    imageUrl: 'миттельшнауцер.jpg',
    name: 'Миттельшнауцер',
    description: 'Характерные черты: окрас «перец с солью» (каждый остевой волосок имеет зоны — белые и чёрные) или чёрный, жёсткая шерсть, квадратный формат, крупная голова с густыми длинными бровями и бородой, морда постепенно сужается от ушей к носу. Уши и хвост как правило ранее купировали.'
  }
];
const currentYear = new Date().getFullYear();
const initialList = ['Керн-терьер', 'Миттельшнауцер', 'Мастиф', 'Корги'];

const App = () => {
  return (
    <div>
      <LandingPage />
      <BreedList breeds={breeds} />
      <DogComponent />
      <List initialList={initialList} />
      <Footer year={currentYear} siteName="Сайт о породах собак" />
    </div>
  );
};
export default App;