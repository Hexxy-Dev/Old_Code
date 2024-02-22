import React, {  } from "react";

import Bottom from "../bottom/bottom";
import Projects_List from "./projects_data";

const ProjectItem = ({id, imagePath, imageAlt, gitLink, description}) => {
  return(
  <div className="projects__item">
    <img src={imagePath} alt={imageAlt}/>
    <div className="projects__btns">
      <a href={"/project/"+id} className="projects__btn">
        <i className="fas fa-eye"></i> View
      </a>
      <a href={gitLink} className="projects__btn">
        <i className="fab fa-github"></i> Github
      </a>
    </div>
    {description()}
  </div>
  );
};

const Projects = () => {
  return(
    <main>
      <section className="projects">
        <div className="projects__bio__image">
          <h1 className="text-secondary">My Projects</h1>
        </div>

        <div className="projects__items">
          {Projects_List.map((project)=>{
            return(
              <ProjectItem key={project.id} {...project}></ProjectItem>
            );})}
        </div>

        <Bottom/>
      </section>
    </main>
  );
};

export default Projects;