import React, { useState, useEffect, useRef } from "react";
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import axios from 'axios';
import { Button } from '../Components/Button';
import { Dropdown } from '../Components/Dropdown';
import  TextBox  from '../Components/TextBox';



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
  const handleRowClick = (row) => {
    console.log('Clicked row:', row);

  };

  const tdStyle = {
    textAlign: 'right'
  };

  const thStyle = {
    textAlign: 'right'
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
                <tr key={item.id} onClick={() => {handleRowClick(item)}}>
                  <td>{item.id}   </td>
                  <td style={tdStyle}>{item.name}
                  </td>
                  <td style={tdStyle}>
                  {Button && 
                    <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall'>
                      Collections
                    </Button>}
                  {Button && 
                    <Button buttonStyle='btn--outline' buttonSize='btn--small' onClick={handleDelete}> 
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

const handleDelete = async (item) => {
  try {
    const response = await axios.delete(`https://54.177.181.151:4000/listDBs/${item}`);
    console.log(response.data); // Optional: Handle the response data

    // Perform any necessary actions after successful deletion

  } catch (error) {
    console.error('Error deleting entry:', error);
    // Handle error case
  }
};

export default ViewDataBase;