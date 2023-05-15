import React, { useState, useEffect, useRef } from "react";
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import axios from 'axios';
import { Button } from '../Components/Button';
import { Dropdown } from '../Components/Dropdown';
import TextBox from '../Components/TextBox';
import PopupGfg from "../Components/Popup";

const ViewDataBase = () => {
  const [data, setData] = useState([]);
  const [newDbCreated, setNewDbCreated] = useState(false);

  useEffect(() => {
    axios.get('https://54.177.181.151:4000/listDBs')
      .then(response => {
        setData(response.data);
      })
      .catch(error => {
        console.log(error);
      });
  }, [newDbCreated]);

  const handleNewDbCreated = () => {
    setNewDbCreated(true);
  }

  return (
      <div className="container">
          <div class="topbar">
              <h1>
                  RestDB+
              </h1>
          </div>
      
          <div className="bottombar">
                      <div className="sidebar">
                        <div className="textbox">
                            <TextBox/>
                          </div>
                          <div className="dropdown">
                            <Dropdown>
                              
                            </Dropdown>
                          </div>
                      </div>


                      <div className="main-content">
                          <table>
                            <thead>
                              <tr>
                               <th>DataBase ID</th>
                                <th>DataBase Name</th>
                              </tr>
                            </thead>
                            <tbody>
                              {data.map((item) => (
                              <tr key={item.id}>
                                <td>{item.id}</td>
                                <td>{item.name}</td>
                              </tr>
                              ))}
                            </tbody>
                          </table>

                      </div>
              </div>
          </div>
  )
}

export default ViewDataBase;