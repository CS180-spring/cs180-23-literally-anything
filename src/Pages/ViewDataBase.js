import React, { createContext, useState, useEffect, } from "react";
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import { Button } from '../Components/Button';
import TextBox from '../Components/TextBox';
import { Dropdown }  from "../Components/Dropdown";

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

  const handleRowClick = (item) => {
    console.log('Clicked row:', item);
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

  const handlePageRefresh = () => {
    window.location.reload();
  }

  const handleCollections = (item) => {
    handleRowClick(item);
    const data = item.data;
    navigate('/Collections');
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
          <Dropdown/>
          
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
                    <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleCollections(item)}}>
                      Collections
                    </Button>}
                  {Button && 
                    <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleDelete(item); handlePageRefresh();}}> 
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