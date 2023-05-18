import React, { useState, useEffect } from "react";
import axios from "axios";
import { Button } from "../Components/Button";
import { useNavigate } from "react-router-dom";
import ViewDataBase from './ViewDataBase';
import './Documents.css'

const Documents = () => {
  const [databases, setDatabases] = useState([]);

  useEffect(() => {
    axios
      .get("https://54.177.181.151:4000/listDBs")
      .then((response) => {
        setDatabases(response.data);
      })
      .catch((error) => {
        console.log(error);
      });
  }, []);

  const tdStyle = {
    textAlign: 'center'
  };

  const thStyle = {
    textAlign: 'center'
  };

  return (
    <div className="documents-container">
      <div className="sidebar" id = "sidebar">
        <h2>Databases</h2>
        <ul>
          {databases.map(database => (
            <li key={database.id}>{database.name}</li>
          ))}
        </ul>
      </div>
      <div className="content">
        <div className="table">
          <table>
            <thead>
              <tr>
                <th>Document ID</th>
                </tr>
            </thead>
          </table>
        </div>
      </div>
      
    </div>
  );
};

export default Documents;
