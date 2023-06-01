import React from 'react';
import { Button } from './Button';
import axios from 'axios';

const TextBoxDoc = (db_id, coll_id) => {

  const handleButtonClick = () => {
    axios.post('https://54.177.181.151:4000/createDocument', {
        db_id: db_id.db_id,
        coll_id: db_id.coll_id
    })
      .then(function(response) {
        window.location.reload();
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });

  };


  return (
    <div>

    <div className="button">
      {Button && <Button buttonStyle='btn--outline' buttonSize='btn--large' onClick={handleButtonClick}> Create Document
      </Button>}
      </div>
    </div>
  );
};

export default TextBoxDoc;