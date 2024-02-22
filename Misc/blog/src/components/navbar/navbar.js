import React, { useState } from 'react'

import { Link, useLocation } from 'react-router-dom'


const Option = ({isOpen, pathname, message}) => {
  const location = useLocation();
  const isActivePage = (pathname) => {
    if(location.pathname === pathname)
      return " active";
    else
      return "";
  };
  const className ="nav__list__item "+ isOpen + isActivePage(pathname);
  return(
    <li className={className}>
      <Link to={pathname}>{message}</Link>
    </li>
  );
}

const Navbar = () => {
  const [isOpen,setIsOpen] = useState("open");
  return(
    <header>
      <nav className={"nav " + isOpen}>
        <div className={"nav__btn"} onClick={() => { setIsOpen(isOpen?"":"open") }}>
          <span className={"nav__btn__burger " + isOpen}></span>
        </div>
        <ul className={"nav__list " + isOpen}>
          <Option isOpen={isOpen} pathname="/" message="Home" />
          <Option isOpen={isOpen} pathname="/about" message="About" />
          <Option isOpen={isOpen} pathname="/projects" message="Projects" />
        </ul>
      </nav>
    </header>
  );
};

export default Navbar;
