import React, {  } from "react";
import { useParams } from "react-router";

import Bottom from "../bottom/bottom";
import Projects_List from "./projects_data";
import Error from "../error/error";

const Project = () => {
  const {id} = useParams();
  if(id < 0 || id > Projects_List.length)
    return(<Error />);
  const project = Projects_List.find(project => { return project.id == id });
  return(
    <main>
      <section className="project">
        <h1>{project.description()}</h1>

        {project.content()}

        <Bottom/>
      </section>
    </main>
  );
};

export default Project;