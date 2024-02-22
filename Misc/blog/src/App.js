import React, {  } from "react";
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom'

import Navbar from "./components/navbar/navbar";
import Home from "./components/home/home";
import About from "./components/about/about";
import Projects from "./components/projects/projects"
import Project from "./components/projects/project";
import Error from "./components/error/error";

function App() {
  return (
    <Router>
      <Navbar />
      <Switch>
        <Route exact path="/">
          <Home />
        </Route>
        <Route path="/about">
          <About />
        </Route>
        <Route path="/projects">
          <Projects />
        </Route>
          <Route path="/project/:id" children={<Project />}></Route>
        <Route path="*">
          <Error />
        </Route>
      </Switch>
  </Router>
  );
}

export default App;
