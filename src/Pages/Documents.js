import React, { useState, useEffect } from "react";
import TextBoxColl from '../Components/TextBoxColl';
import axios from "axios";
import { Button } from "../Components/Button";
import { useNavigate, Link, useLocation } from 'react-router-dom';
import ViewDataBase from './ViewDataBase';
import './Documents.css'


const Documents = () => {
  const [data, setData] = useState([]);
  const navigate = useNavigate();
  const location = useLocation();
  

  useEffect(() => {
    axios.get('https://54.177.181.151:4000/listDocuments', {
        params: {
            "db_id": location.state.db_id,
            "coll_id": location.state.coll_id
        }
    })
        .then(response => {
            setData(response.data);
        })
        .catch(error => {
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
    <div className="Documents">
      <div className="container">
        <div className="left-collumn">
          <h1>ReactDB</h1>
            <TextBoxColl db_id={location.state.id}/>
        </div>
        <div className="main_content">
          <div className="table_container">
            <table>
              <thead>
                <tr>
                  <th>Document ID</th>
                  <th style={thStyle}>Collection Name</th>
                  <th style={thStyle}>View Documents or Delete</th>
                </tr>
              </thead>
              <tbody>
                {data.map((item) => (
                  <tr key={item.id}>
                  <td> {item.id} </td>
                  <td style={tdStyle}> {item.coll_id} </td>
                  <td style={tdStyle}>
                  {Button && 
                      <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' >
                          Edit
                      </Button>}
                  {Button && 
                      <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' > 
                          Delete
                      </Button>}
                  </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Documents;