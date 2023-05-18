import React, { useState, useEffect, useRef } from "react";
import { useNaviagate, Route, useNavigate, Link, Routes } from 'react-router-dom';
import axios from 'axios';
import { Button } from '../Components/Button';
import { Dropdown } from '../Components/Dropdown';
import  TextBox  from '../Components/TextBox';



const ViewDataBase = () => {
  const [data, setData] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    axios.get('https://54.177.181.151:4000/listDBs')
      .then(response => {
        setData(response.data);
      })
      .catch(error => {
        console.log(error);
      });
  }, []);

  const handleRowClick = (row) => {
    console.log('Clicked row:', row);
  };

  const handleDelete = (item) => {
    console.log('Clicked');
    handleRowClick(item);
    axios.post('https://54.177.181.151:4000/deleteDB', {
        db_id: item.id
    })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error.response.data);
      });
  };

  const handleCollections = () => {
    navigate('/Collections.js');
  }

  const tdStyle = {
    textAlign: 'center'
  };

  const thStyle = {
    textAlign: 'center'
  }

  return (
      <div className="container">
        <div className="left_column">
          <h1>ReactDB+</h1>
          <TextBox/>
          
        </div>

        <div className="main_content">
          <div className="table_container">
            <table>
              <thead>
                <tr>
                  <th>DataBase ID</th>
                  <th style={thStyle}>DataBase Name</th>
                  <th style={thStyle}>View Collections or Delete</th>
                </tr>
              </thead>
              <tbody>
                {data.map((item) => (
                <tr key={item.id}>
                  <td> {item.id} </td>
                  <td style={tdStyle}> {item.name} </td>
                  <td style={tdStyle}>
                  {Button && 
                    <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={handleCollections}>
                      Collections
                    </Button>}
                  {Button && 
                    <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleDelete(item)}}> 
                      DeleteDB
                    </Button>}
                  </td>
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