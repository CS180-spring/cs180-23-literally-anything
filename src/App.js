import './App.css';
import { Routes, Route, HashRouter } from 'react-router-dom';
// import Home from './Pages/Home'
import ViewDataBase from './Pages/ViewDataBase';
import NoPage from './Pages/NoPage';
import axios from 'axios';
import Collections from './Pages/Collections';

axios.get('https://54.177.181.151:4000/listDBs')
  .then(response => {
    console.log(response.data);
  })
  .catch(error => {
    console.error(error);
  });

function App() {


  return (
    <div className="App">
      <HashRouter>
        <Routes>
          <Route index element={<ViewDataBase />}/>
          <Route path="/viewDataBase" element={<ViewDataBase />} />
          <Route path="/Collections" element={<Collections />} />
          <Route path="*" element={<NoPage />} />
        </Routes>
      </HashRouter>

    </div>
  );
}

export default App;
