import React from 'react';
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';
import { Button } from './Button';
 
export default function PopupGfg() {
    return (
        <div>
            <Popup trigger=
                {Button && <Button buttonstyle='btn--outline' buttonSize='btn--large'> Create DataBase </Button>}
                position="right center">
                <button>Create DataBase</button>
            </Popup>
        </div>
    )
};