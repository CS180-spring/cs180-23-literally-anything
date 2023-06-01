import React, { useState, useEffect } from "react";
import TextBoxDoc from '../Components/TextBoxDoc';
import TextBoxSearch from '../Components/TextBoxSearch';

import axios from "axios";
import { Button } from "../Components/Button";
import { useNavigate, useLocation } from 'react-router-dom';
import './Documents.css';
import Dinosaur from "../assets/Dinosaur.png";


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
    }, [location.state]);

    const handleRowClick = (item) => {
      console.log('Clicked row:', item);
  };

    const handleEdit = (item) => {
      handleRowClick(item);
      navigate('/EditDocument', {state:{db_id:location.state.db_id, coll_id:location.state.coll_id, doc_id:item.id}});
    }
    

    const handleDelete = (item) => {
      handleRowClick(item);
      axios.post('https://54.177.181.151:4000/deleteDoc', {
            "db_id": location.state.db_id,
            "coll_id": location.state.coll_id,
            "doc_id": item.id
        })
        .then(function(response) {
          window.location.reload();
          console.log(response.data)
        })
        .catch(error => {
            console.log(error);
        });
    };

    const handleSearch = () => {
      navigate('/Search', {state:{db_id:location.state.db_id, coll_id:location.state.coll_id}});
    }


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
        <img src={Dinosaur} id="dino-img" alt="dinosaur-logo"/>
          <h1>DinoDB</h1>
            <TextBoxDoc db_id={location.state.db_id} coll_id={location.state.coll_id} />
            <TextBoxSearch db_id={location.state.db_id} coll_id={location.state.coll_id} />

        </div>
        <div className="main_content">
          <div className="table_container">
            <table>
              <thead>
                <tr>
                  <th>Document ID</th>
                  <th style={thStyle}>Document Data</th>
                  <th style={thStyle}>Edit Documents or Delete</th>
                </tr>
              </thead>
              <tbody>

                {data.map((item) => (
                  <tr key={item.id}>
                  <td> {item.id} </td>
                  <td style={tdStyle}> {location.state.coll_id} </td>
                  <td style={tdStyle}>
                  {Button && 
                      <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleEdit(item)}}>
                          Edit
                      </Button>}
                  {Button && 
                      <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleDelete(item)}}> 
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