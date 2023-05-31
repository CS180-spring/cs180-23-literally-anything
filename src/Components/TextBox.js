import React, { useState } from 'react';
import { Button } from './Button';
import axios from 'axios';
import './TextBoxColl.css'

const TextBox = () => {
  const [isOpen, setIsOpen] = useState(false);
  const [userInput, setUserInput] = useState('');

  const handleButtonClick = () => {
    setIsOpen(true);
    
  };

  const handleInputChange = (event) => {
    setUserInput(event.target.value);
  };

  const handleFormSubmit = (event) => {
    event.preventDefault();
    console.log('User input:', userInput);
    setIsOpen(false);
    process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;
    
    axios.post('https://54.177.181.151:4000/createDB', {
      name: userInput
    })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });
  };

  return (
    <div>

    <div className="button">
      {Button && <Button buttonStyle='btn--outline' buttonSize='btn--large' onClick={handleButtonClick}> Create Database
      </Button>}
      {isOpen && (
        <form onSubmit={handleFormSubmit}>
          <input type="text" value={userInput} onChange={handleInputChange} />
          <Button buttonStyle = 'btn--outline' buttonSize='btn--small'  type="submit" >
            Submit New Database
          </Button>
        </form>
      )}
    </div>
  </div>
  );
};

export default TextBox;