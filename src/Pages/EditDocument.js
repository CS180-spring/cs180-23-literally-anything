import React, { useState, useEffect } from "react";
import axios from "axios";
import { useNavigate, Link, useLocation } from 'react-router-dom';
import Dinosaur from "../assets/Dinosaur.png";

const EditDocument = ({ object }) => {

  const [text, setText] = useState(JSON.stringify(object, null, 2));
  const navigate = useNavigate();
  const location = useLocation();


  useEffect(() => {
    axios.get('https://54.177.181.151:4000/fetchDocument', {
        params: {
            "db_id": location.state.db_id,
            "coll_id": location.state.coll_id,
            "doc_id": location.state.doc_id
        }
    })
        .then(response => {
          setText(JSON.stringify(response.data));
        })
        .catch(error => {
            console.log(error);
        });
    }, []);


  const handleChange = (event) => {
    setText(event.target.value);
  };

  const handleSave = () => {
    try {
      const updatedObject = JSON.parse(text);
      // Do something with the updated object, like saving it to a backend API
      console.log(updatedObject);
      axios.post('https://54.177.181.151:4000/updateDocument',updatedObject,
        {
          params: {
            db_id: location.state.db_id,
            coll_id: location.state.coll_id,
            doc_id: location.state.doc_id,
          }
        }
      )
      .then(function(response) {
        console.log(response.data);
        console.log(location.state.db_id);

          console.log(location.state.coll_id);
            console.log(location.state.doc_id);
      })
      .catch(function(error) {
        console.log(error.response.data);
      });

    } catch (error) {
      console.error('Invalid JSON format');
      alert('Invalid JSON format');
    }
  };

  return (
    <div className='EditDocument'>
        <div className='container'>

        <div className="left-collumn">
            <img src={Dinosaur} id="dino-img" alt="dinosaur-logo"/>
            <h1>DinoDB</h1>
        </div>

        <div className='main_content'>
          <div className="edit_container">
            <textarea value={text} onChange={handleChange} rows={40} cols={100} />
            <button className="save_button" onClick={handleSave}>Save</button>
          </div>
        </div>
        
        </div>
    </div>
  );
};

export default EditDocument;
