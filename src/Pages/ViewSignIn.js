import React, { createContext, useState, useEffect, } from "react";
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import Dinosaur from "../assets/Dinosaur.png";

  const handleRowClick = (item) => {
    console.log('Clicked row:', item); //used to track what row is clicked when interacting with table
  };

  const handleDelete = (item) => {
    console.log('Clicked');
    handleRowClick(item);
    axios.post('https://54.177.181.151:4000/deleteDB', { //used to delete database from table/server
        db_id: item.id
    })
      .then(function(response) {
        window.location.reload();
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error.response.data);
      });
  };

  const handleCollections = (item) => {
    handleRowClick(item);
    const data = item.data;
    navigate('/Collections', {state:{id:item.id}}); //navigate to collections page
  }

  return (

      <div className="Databases">
        <div className="container">
          <div className="left_column">
            <img src={Dinosaur} id="dino-img" alt="dinosaur-logo"/>
            <h1>DinoDB+</h1>
          </div>

          <div className="main_content">

          </div>
        </div>
      </div>
  )
}

export default ViewSignIn;