import React, { useState } from "react";
import axios from "axios";
import { useNavigate, useLocation } from 'react-router-dom';
import { Button } from "../Components/Button";
import Dinosaur from "../assets/Dinosaur.png";
import './Documents.css';

const Search = ({ object }) => {
    const [text, setText] = useState(JSON.stringify(object, null, 2));
    const navigate = useNavigate();
    const location = useLocation();
    const [searchResults, setsearchResults] = useState();

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

    return (
        <div className='Search'>
            <div className='container'>
    
            <div className="left-collumn">
            <img src={Dinosaur} id="dino-img" alt="dinosaur-logo"/>
                <h1>DinoDB+</h1>
            </div>
    
            <div className='main_content'>
              <div className="edit_container">
              <div className="search_container">
              <div className="query">
                Query: {JSON.stringify(location.state.query)}
                </div>
                <div className="results">


                  <div className="main_content">
                    <div className="table_container">
                      <table>
                        <thead>
                          <tr>
                            <th>Results</th>
                          </tr>
                        </thead>
                        <tbody>

                          {location.state.res.map((item) => (
                            <tr>
                              <td> {item.id} </td>
                            <td> {JSON.stringify(item.body)} </td>
                            <td> 
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
              </div>
            </div>
            </div>
        </div>
      );
}

export default Search;
