import Header from '../Components/Header'
import React, { useState, useEffect, useRef } from "react";
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import axios from 'axios';

const ViewDataBase = () => {
  const [data, setData] = useState([]);

  useEffect(() => {
    axios.get('https://54.177.181.151:4000/listDBs')
      .then(response => {
        setData(response.data);
      })
      .catch(error => {
        console.log(error);
      });
  }, []);

  return (
      <div className="container">
          <div class="topbar">
              <h1>
                  test
              </h1>
          </div>
      
          <div className="bottombar">
                      <div className="sidebar">
                          <h1>Create Database button</h1>

                          <h3>other database view here</h3>
                      </div>


                      <div className="main-content">
                          <Header />
                          <h2> View Database Page </h2>
                          
                          <table>
                            <thead>
                              <tr>
                               <th>DataBase ID</th>
                                <th>DataBase Name</th>
                              </tr>
                            </thead>
                            <tbody>
                              {data.map((item) => (
                              <tr key={item.db_id}>
                                <td>{item.db_id}</td>
                                <td>{item.db_name}</td>
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
