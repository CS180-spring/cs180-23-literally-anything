import React, { useState, useEffect } from "react";
import axios from "axios";
import { useNavigate, Link, useLocation } from 'react-router-dom';
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
            setText(response.data.content);
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
      axios.post('https://54.177.181.151:4000/updateDoctument', {
            db_id: location.state.db_id,
            coll_id: location.state.coll_id,
            doc_id: location.state.doc_id,
            content: updatedObject
      })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error.response.data);
      });
    } catch (error) {
      console.error('Invalid JSON format');
    }
  };

  return (
    <div className='EditDocument'>
        <div className='contained'>

        <div className="left-collumn">
            <h1>ReactDB</h1>
        </div>

        <div className='main_content'>

            <textarea value={text} onChange={handleChange} rows={10} cols={50} />
            <button onClick={handleSave}>Save</button>
        </div>
        
        </div>
    </div>
  );
};

export default EditDocument;
