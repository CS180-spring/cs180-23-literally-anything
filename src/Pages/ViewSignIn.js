import React, { createContext, useState, useEffect, } from "react";
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import { Button } from '../Components/Button';
import TextBox from '../Components/TextBox';
import Dinosaur from "../assets/Dinosaur.png";

const ViewSignIn = () => {
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

  const tdStyle = { //in line styling
    textAlign: 'center'
  };

  const thStyle = {
    textAlign: 'center'
  }

  return (

      <div className="Databases">
        <div className="container">
          <div className="left_column">
            <img src={Dinosaur} id="dino-img" alt="dinosaur-logo"/>
            <h1>DinoDB+</h1>
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
                  {data.map((item) => ( //inputting data from array into table
                  <tr key={item.id}>
                    <td> {item.id} </td>
                    <td style={tdStyle}> {item.name} </td>
                    <td style={tdStyle}>
                    {Button && //collections navigation button
                      <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleCollections(item)}}>
                        Collections
                      </Button>}
                    {Button && //delete db button
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
      </div>
  )
}

export default ViewSignIn;