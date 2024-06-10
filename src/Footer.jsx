import React from 'react';

const Footer = (props) => {
  const { year, siteName } = props;

  return (
    <footer>
      <p>&copy; {year} {siteName}</p>
    </footer>
  );
};

export default Footer;