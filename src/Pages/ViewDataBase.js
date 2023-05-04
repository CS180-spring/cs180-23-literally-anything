import Header from '../Components/Header'
import React, { useRef } from "react";
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import axios from 'axios';
import { createCollection } from '../Components/AxiosFunctions';


export default function ViewDataBase() {
  

    const createCollection = () => {
        axios.get('http://54.183.24.168:4000/createCollection')
        .then(response => {
          console.log(response.data);
        })
        .catch(error => {
          console.error(error);
        });
      }
    return (
        <div className="container">
            <div class="topbar">
                <h1>
                    test
                </h1>
            </div>
        
            <div className="bottombar">
                        <div className="sidebar">
                            
                        </div>


                        <div className="main-content">
                            <Header />
                            <h2> View Database Page </h2>
                        </div>
            </div>
            <button onClick={createCollection}> Create Collection </button>
        </div>
    )
}
