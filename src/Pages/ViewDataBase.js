import React, { useState, useEffect, useRef } from "react";
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import axios from 'axios';
import { Button } from '../Components/Button';
import { Dropdown } from '../Components/Dropdown';

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
        <div className="left_column">
          <h1>asdf</h1>
        </div>

        <div className="main_content">
          <div className="table_container">
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