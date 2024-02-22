import React, {  } from "react";

import Bottom from "../bottom/bottom";

const Bio_description = () => {
  return(
  <p>
    // REDACTED
  </p>
  );
}

const Jobs = [
  { id:2,
    period:"",// REDACTED
    company:"",// REDACTED
    position:"Student",
    description:()=>{return(
    <p>
      // REDACTED
    </p>
  );}},

  { id:1,
    period:"",// REDACTED
    company:"",// REDACTED
    position:"Student",
    description:()=>{return(
    <p>
      // REDACTED
    </p>
  );}},
];

const Job = ({period, company, position, description}) => {
  return(
    <div className="jobs__job">
      <h2>{period}</h2>
      <h3>{company}</h3>
      <h5>{position}</h5>
      {description()}
    </div>
  );
};

const About = () => {
  return(
    <main>
      <section className="about">
        <div className="about__bio__image">
          <div className="about__bio">
            <h2>BIO</h2>
            {Bio_description()}
          </div>
        </div>
        <div className="jobs">
          {Jobs.map((job)=>{
            return(
              <Job key={job.id} {...job}/>
            );
          })}
        </div>

        <Bottom/>
      </section>
    </main>
  );
};

export default About;