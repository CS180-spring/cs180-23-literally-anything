import TextBoxColl from '../Components/TextBoxColl';
import React, { useState, useEffect } from "react";
import { useNavigate, useLocation } from 'react-router-dom';
import axios from 'axios';
import { Button } from '../Components/Button';
import Dinosaur from "../assets/Dinosaur.png";

function Collections() {
    const [data, setData] = useState([]);
    const navigate = useNavigate();
    const location = useLocation();


    useEffect(() => {
        axios.get('https://54.177.181.151:4000/listCollection', {
            params: {
                "db_id" : location.state.id
            }
        })
            .then(response => {
                setData(response.data);
                console.log(response.data)
            })
            .catch(error => {
                console.log(error);
            });
        }, [location.state]);

    const handleDelete = (item) => {
            console.log('Clicked');
            handleRowClick(item);
            axios.post('https://54.177.181.151:4000/deleteColl', {
                "db_id" : location.state.id,
                "coll_id" : item.id
            })
              .then(function(response) {
                window.location.reload();
                console.log(response.data);
              })
              .catch(function(error) {
                console.log(error.response.data);
              });
        };
        const handleRowClick = (item) => {
        console.log('Clicked row:', item);
    };
    
    const handleDocument = (item) => {
        handleRowClick(item);
        const data = item.data;
        navigate('/Documents', {state:{db_id:location.state.id, coll_id:item.id}});
      }

    const tdStyle = {
        textAlign: 'center'
      };
    
      const thStyle = {
        textAlign: 'center'
      }

    return(
        <div className="Collections">
            <div className="container">
                <div className="left_column">
                <img src={Dinosaur} id="dino-img" alt="dinosaur-logo"/>
                    <h1>DinoDB+</h1>
                        <TextBoxColl db_id={location.state.id}/>
                </div>
                <div className="main_content">
                    <div className="table_container">
                        <table>
                            <thead>
                                <tr>
                                    <th>Collection ID</th>
                                    <th style={thStyle}>Collection Name</th>
                                    <th style={thStyle}>View Documents or Delete</th>
                                </tr>
                            </thead>
                            <tbody>
                                {data.map((item) => (
                                <tr key={item.id}>
                                <td> {item.id} </td>
                                <td style={tdStyle}> {item.name} </td>
                                <td style={tdStyle}>
                                {Button && 
                                    <Button buttonStyle='btn--outline' buttonSize='btn--xtrasmall' onClick={() => {handleDocument(item)}}>
                                        Documents
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
    )
}

export default Collections;