import React, {  } from "react";

import Bottom from "../bottom/bottom";

const Home = () => {
  return(
    <main>
      <section className="home">
        <h2>Hi! My Name Is</h2>
        <h1 className="home__name">
          <span className="home__name--last">Hexxy</span>
        </h1>
        <h2>Student, Sysadmin & Programmer</h2>

        <Bottom/>
      </section>
    </main>
  );
};

export default Home;