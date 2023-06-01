import React, { useState } from 'react';
import { Button } from './Button';
import axios from 'axios';
import { useNavigate, useLocation } from 'react-router-dom';


const TextBoxSearch = (db_id) => {
  const [isOpen, setIsOpen] = useState(false);
  const [userInput, setUserInput] = useState('');
  const navigate = useNavigate();
  const location = useLocation();


  const handleButtonClick = () => {
    setIsOpen(true);
    
  };

  const handleInputChange = (event) => {
    setUserInput(event.target.value);
  };

  const handleFormSubmit = (event) => {
    event.preventDefault();
    setIsOpen(false);
    console.log(userInput);
    process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;

    try {
      const updatedObject = JSON.parse(userInput);
      // Do something with the updated object, like saving it to a backend API
      //console.log(updatedObject);
      console.log(updatedObject);
      console.log(db_id.db_id);
      console.log(db_id.coll_id);
      
      axios.post('https://54.177.181.151:4000/searchContent',{
            "db_id":db_id.db_id,
            "coll_id":db_id.coll_id,
            "query":updatedObject,

        }
      )
      .then(function(response) {
        console.log(response.data);
        navigate('/Search', {state:{db_id:db_id.db_id, coll_id:db_id.coll_id, res:response.data}});
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
    <div>

    <div className="button">
      {Button && <Button buttonStyle='btn--outline' buttonSize='btn--large' onClick={handleButtonClick}> Search
      </Button>}
      {isOpen && (
        <form onSubmit={handleFormSubmit}>
          <input type="text" value={userInput} style={{textAlign: 'center', width: 170}} placeholder="Type a query: {field: value}" onChange={handleInputChange} />
          <Button buttonStyle = 'btn--outline' buttonSize='btn--small'  type="submit" >
            Search
          </Button>
        </form>
      )}
      </div>
    </div>
  );
};

export default TextBoxSearch;