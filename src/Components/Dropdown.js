import React, { useState } from 'react'
import Dropdown from './Dropdown'

function Dropdown () {
    const [state, setstate] = useState(false);
    const showDropdown=()=> {
        setstate(true);
    }
    const hideDropdown=()=> {
        setstate(false);
    }
    return (
        <div className="Dropdown">
            <div classNmae="dropdown-menu" onMouseEnter={showDropdown} onMouseLeave={hideDropdown}>
                DataBase

                <ul>
                    <li>     Collection 1</li>
                    <li>     Collection 2</li>
                    <li>     Collection 3</li>
                    <li>     Collection 4</li>
                </ul>
            </div>
        </div>
    )
}
